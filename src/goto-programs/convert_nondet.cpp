/*******************************************************************\

Module: Convert side_effect_expr_nondett expressions

Author: Reuben Thomas, reuben.thomas@diffblue.com

\*******************************************************************/

/// \file
/// Convert side_effect_expr_nondett expressions

#include "convert_nondet.h"
#include "goto_convert.h"
#include "goto_model.h"
#include "remove_skip.h"

#include <java_bytecode/java_object_factory.h> // gen_nondet_init

#include <util/irep_ids.h>

#include <memory>

/// Checks an instruction to see whether it contains an assignment from
/// side_effect_expr_nondet.  If so, replaces the instruction with a range of
/// instructions to properly nondet-initialize the lhs.
/// \param goto_program: The goto program to modify.
/// \param target: One of the steps in that goto program.
/// \param symbol_table: The global symbol table.
/// \param message_handler: Handles logging.
/// \param max_nondet_array_length: Maximum size of new nondet arrays.
/// \return The next instruction to process with this function.
static goto_programt::targett insert_nondet_init_code(
  goto_programt &goto_program,
  const goto_programt::targett &target,
  symbol_tablet &symbol_table,
  message_handlert &message_handler,
  const object_factory_parameterst &object_factory_parameters)
{
  // Return if the instruction isn't an assignment
  const auto next_instr=std::next(target);
  if(!target->is_assign())
  {
    return next_instr;
  }

  // Return if the rhs of the assignment isn't a side effect expression
  const auto &assign=to_code_assign(target->code);
  if(assign.rhs().id()!=ID_side_effect)
  {
    return next_instr;
  }

  // Return if the rhs isn't nondet
  const auto &side_effect=to_side_effect_expr(assign.rhs());
  if(side_effect.get_statement()!=ID_nondet)
  {
    return next_instr;
  }

  const auto lhs=assign.lhs();
  // If the lhs type doesn't have a subtype then I guess it's primitive and
  // we want to bail out now
  if(!lhs.type().has_subtype())
  {
    return next_instr;
  }

  // Although, if the type is a ptr-to-void then we also want to bail
  if(lhs.type().subtype().id()==ID_empty ||
     lhs.type().subtype().id()==ID_code)
  {
    return next_instr;
  }

  // Check whether the nondet object may be null
  const auto nullable=to_side_effect_expr_nondet(side_effect).get_nullable();
  // Get the symbol to nondet-init
  const auto source_loc=target->source_location;

  // Erase the nondet assignment
  target->make_skip();

  // Generate nondet init code
  code_blockt init_code;
  gen_nondet_init(
    lhs,
    init_code,
    symbol_table,
    source_loc,
    true,
    allocation_typet::DYNAMIC,
    nullable,
    object_factory_parameters,
    update_in_placet::NO_UPDATE_IN_PLACE);

  // Convert this code into goto instructions
  goto_programt new_instructions;
  goto_convert(init_code, symbol_table, new_instructions, message_handler);

  // Insert the new instructions into the instruction list
  goto_program.destructive_insert(next_instr, new_instructions);
  goto_program.update();

  return next_instr;
}

/// For each instruction in the goto program, checks if it is an assignment from
/// nondet and replaces it with the appropriate composite initialization code if
/// so.
/// \param goto_program: The goto program to modify.
/// \param symbol_table: The global symbol table.
/// \param message_handler: Handles logging.
/// \param max_nondet_array_length: Maximum size of new nondet arrays.
void convert_nondet(
  goto_programt &goto_program,
  symbol_tablet &symbol_table,
  message_handlert &message_handler,
  const object_factory_parameterst &object_factory_parameters)
{
  for(auto instruction_iterator=goto_program.instructions.begin(),
        end=goto_program.instructions.end();
      instruction_iterator!=end;)
  {
    instruction_iterator=insert_nondet_init_code(
      goto_program,
      instruction_iterator,
      symbol_table,
      message_handler,
      object_factory_parameters);
  }
}

void convert_nondet(
  goto_functionst &goto_functions,
  symbol_tablet &symbol_table,
  message_handlert &message_handler,
  const object_factory_parameterst &object_factory_parameters)
{
  const namespacet ns(symbol_table);

  for(auto &f_it : goto_functions.function_map)
  {
    const symbolt &symbol=ns.lookup(f_it.first);

    if(symbol.mode==ID_java)
    {
      convert_nondet(
        f_it.second.body,
        symbol_table,
        message_handler,
        object_factory_parameters);
    }
  }

  goto_functions.compute_location_numbers();

  remove_skip(goto_functions);
}

void convert_nondet(
  goto_modelt &goto_model,
  message_handlert &message_handler,
  const object_factory_parameterst& object_factory_parameters)
{
  convert_nondet(
    goto_model.goto_functions,
    goto_model.symbol_table,
    message_handler,
    object_factory_parameters);
}
