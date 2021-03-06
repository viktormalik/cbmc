/*******************************************************************\

 Module: Unit tests for parsing generic classes

 Author: DiffBlue Limited. All rights reserved.

\*******************************************************************/

#include <testing-utils/catch.hpp>
#include <testing-utils/require_symbol.h>
#include <testing-utils/require_type.h>

#include <util/cmdline.h>
#include <util/config.h>
#include <util/language.h>
#include <util/prefix.h>
#include <util/std_types.h>

#include <java_bytecode/java_bytecode_language.h>

#include <iostream>
#include <testing-utils/load_java_class.h>

SCENARIO(
  "Parse fields of inner classes on a generic class",
  "[core][java_bytecode][java_bytecode_parse_generics]")
{
  const symbol_tablet &new_symbol_table = load_java_class(
    "GenericClass", "./java_bytecode/java_bytecode_parse_generics");

  std::string class_prefix = "java::GenericClass";
  THEN("There should be a symbol for GenericClass with correct components")
  {
    REQUIRE(new_symbol_table.has_symbol(class_prefix));
    const symbolt &class_symbol = new_symbol_table.lookup_ref(class_prefix);

    const class_typet &class_type =
      require_symbol::require_complete_class(class_symbol);

    THEN("The field component should be a pointer to GenericClass$InnerClass")
    {
      const struct_typet::componentt &field_component =
        require_type::require_component(class_type, "field");

      require_type::require_pointer(
        field_component.type(), symbol_typet("java::GenericClass$InnerClass"));

      THEN("The pointer should be generic")
      {
        REQUIRE(is_java_generic_type(field_component.type()));
        const auto &generic_variables =
          to_java_generic_type(field_component.type()).generic_type_variables();
        REQUIRE(generic_variables.size() == 1);
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
    }

    THEN("The field component should be a pointer to GenericClass$InnerClass")
    {
      const struct_typet::componentt &field_component =
        require_type::require_component(class_type, "field2");

      require_type::require_pointer(
        field_component.type(),
        symbol_typet("java::GenericClass$GenericInnerClass"));

      THEN("The pointer should be generic")
      {
        REQUIRE(is_java_generic_type(field_component.type()));
        const auto &generic_variables =
          to_java_generic_type(field_component.type()).generic_type_variables();
        REQUIRE(generic_variables.size() == 2);
        {
          const java_generic_parametert &generic_param = generic_variables[0];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param.type_variable() ==
            symbol_typet("java::GenericClass::T"));
        }
        {
          const java_generic_parametert &generic_param = generic_variables[1];
          REQUIRE(is_java_generic_inst_parameter(generic_param));
          REQUIRE(
            generic_param ==
            java_generic_inst_parametert(symbol_typet("java::Foo")));
        }
      }
    }

    THEN(
      "The field component should be a pointer to "
      "GenericClass$GenericInnerClass$DoublyNestedInnerClass")
    {
      const struct_typet::componentt &field_component =
        require_type::require_component(class_type, "field4");

      require_type::require_pointer(
        field_component.type(),
        symbol_typet(
          "java::GenericClass$GenericInnerClass$DoublyNestedInnerClass"));

      THEN("The pointer should be generic")
      {
        REQUIRE(is_java_generic_type(field_component.type()));
        const auto &generic_variables =
          to_java_generic_type(field_component.type()).generic_type_variables();
        REQUIRE(generic_variables.size() == 2);
        {
          const java_generic_parametert &generic_param = generic_variables[0];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param.type_variable() ==
            symbol_typet("java::GenericClass::T"));
        }
        {
          const java_generic_parametert &generic_param = generic_variables[1];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param ==
            java_generic_inst_parametert(symbol_typet("java::Foo")));
        }
      }
    }

    THEN(
      "The field component should be a pointer to "
      "GenericClass$GenericInnerClass$DoublyNestedInnerClass")
    {
      const struct_typet::componentt &field_component =
        require_type::require_component(class_type, "field5");

      require_type::require_pointer(
        field_component.type(),
        symbol_typet(
          "java::GenericClass$GenericInnerClass$DoublyNestedInnerClass"));

      THEN("The pointer should be generic")
      {
        REQUIRE(is_java_generic_type(field_component.type()));
        const auto &generic_variables =
          to_java_generic_type(field_component.type()).generic_type_variables();
        REQUIRE(generic_variables.size() == 2);
        {
          const java_generic_parametert &generic_param = generic_variables[0];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param.type_variable() ==
            symbol_typet("java::GenericClass::T"));
        }
        {
          const java_generic_parametert &generic_param = generic_variables[1];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param.type_variable() ==
            symbol_typet("java::GenericClass::T"));
        }
      }
    }

    THEN(
      "The field component should be a pointer to "
      "GenericClass$GenericInnerClass$DoublyNestedInnerGenericClass")
    {
      const struct_typet::componentt &field_component =
        require_type::require_component(class_type, "field6");

      require_type::require_pointer(
        field_component.type(),
        symbol_typet(
          "java::GenericClass$GenericInnerClass$"
          "DoublyNestedInnerGenericClass"));

      THEN("The pointer should be generic")
      {
        REQUIRE(is_java_generic_type(field_component.type()));
        const auto &generic_variables =
          to_java_generic_type(field_component.type()).generic_type_variables();
        REQUIRE(generic_variables.size() == 3);
        {
          const java_generic_parametert &generic_param = generic_variables[0];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param.type_variable() ==
            symbol_typet("java::GenericClass::T"));
        }
        {
          const java_generic_parametert &generic_param = generic_variables[1];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param ==
            java_generic_inst_parametert(symbol_typet("java::Foo")));
        }
        {
          const java_generic_parametert &generic_param = generic_variables[2];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param ==
            java_generic_inst_parametert(symbol_typet("java::Foo")));
        }
      }
    }

    THEN(
      "The field component should be a pointer to "
      "GenericClass$GenericInnerClass$DoublyNestedInnerGenericClass")
    {
      const struct_typet::componentt &field_component =
        require_type::require_component(class_type, "field7");

      require_type::require_pointer(
        field_component.type(),
        symbol_typet(
          "java::GenericClass$GenericInnerClass$"
          "DoublyNestedInnerGenericClass"));

      THEN("The pointer should be generic")
      {
        REQUIRE(is_java_generic_type(field_component.type()));
        const auto &generic_variables =
          to_java_generic_type(field_component.type()).generic_type_variables();
        REQUIRE(generic_variables.size() == 3);
        {
          const java_generic_parametert &generic_param = generic_variables[0];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param.type_variable() ==
            symbol_typet("java::GenericClass::T"));
        }
        {
          const java_generic_parametert &generic_param = generic_variables[1];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param.type_variable() ==
            symbol_typet("java::GenericClass::T"));
        }
        {
          const java_generic_parametert &generic_param = generic_variables[2];
          REQUIRE(is_java_generic_parameter(generic_param));
          REQUIRE(
            generic_param.type_variable() ==
            symbol_typet("java::GenericClass::T"));
        }
      }
    }
  }
}

SCENARIO(
  "Parse methods of generic classes using inner parameters",
  "[core][java_bytecode][java_bytecode_parse_generics][caskjd]")
{
  const symbol_tablet &new_symbol_table = load_java_class(
    "GenericClass", "./java_bytecode/java_bytecode_parse_generics");

  std::string class_prefix = "java::GenericClass";

  THEN("Method 1 should take a pointer to GenericClass$InnerClass")
  {
    const std::string func_name = ".method";
    const std::string func_descriptor = ":(LGenericClass$InnerClass;)V";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    const auto param_type =
      require_type::require_parameter(function_call, "input");
    require_type::require_pointer(
      param_type.type(), symbol_typet("java::GenericClass$InnerClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(param_type.type()));
      const auto &generic_variables =
        to_java_generic_type(param_type.type()).generic_type_variables();
      REQUIRE(generic_variables.size() == 1);
      const java_generic_parametert &generic_param = generic_variables[0];
      REQUIRE(
        generic_param.type_variable() == symbol_typet("java::GenericClass::T"));
    }
  }
  THEN("Method 2 should take two pointers to GenericClass$InnerClass")
  {
    const std::string func_name = ".method2";
    const std::string func_descriptor =
      ":(LGenericClass$InnerClass;LGenericClass$InnerClass;)V";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    // Check param input
    {
      const auto param_type =
        require_type::require_parameter(function_call, "input");
      require_type::require_pointer(
        param_type.type(), symbol_typet("java::GenericClass$InnerClass"));

      THEN("The pointer should be generic")
      {
        REQUIRE(is_java_generic_type(param_type.type()));
        const auto &generic_variables =
          to_java_generic_type(param_type.type()).generic_type_variables();
        REQUIRE(generic_variables.size() == 1);
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
    }

    // Check param input2
    {
      const auto param_type2 =
        require_type::require_parameter(function_call, "input2");
      require_type::require_pointer(
        param_type2.type(), symbol_typet("java::GenericClass$InnerClass"));

      THEN("The pointer should be generic")
      {
        REQUIRE(is_java_generic_type(param_type2.type()));
        const auto &generic_variables =
          to_java_generic_type(param_type2.type()).generic_type_variables();
        REQUIRE(generic_variables.size() == 1);
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
    }
  }
  THEN("Method 3 should take a pointer to GenericClass$GenericInnerClass")
  {
    const std::string func_name = ".method3";
    const std::string func_descriptor = ":(LGenericClass$GenericInnerClass;)V";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    const auto param_type =
      require_type::require_parameter(function_call, "input");
    require_type::require_pointer(
      param_type.type(), symbol_typet("java::GenericClass$GenericInnerClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(param_type.type()));
      const auto &generic_variables =
        to_java_generic_type(param_type.type()).generic_type_variables();
      REQUIRE(generic_variables.size() == 2);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_inst_parameter(generic_param));
        REQUIRE(
          generic_param ==
          java_generic_inst_parametert(symbol_typet("java::Foo")));
      }
    }
  }
  THEN("Method 4 should take a pointer to GenericClass$GenericInnerClass")
  {
    const std::string func_name = ".method4";
    const std::string func_descriptor = ":(LGenericClass$GenericInnerClass;)V";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    const auto param_type =
      require_type::require_parameter(function_call, "input");
    require_type::require_pointer(
      param_type.type(), symbol_typet("java::GenericClass$GenericInnerClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(param_type.type()));
      const auto &generic_variables =
        to_java_generic_type(param_type.type()).generic_type_variables();
      REQUIRE(generic_variables.size() == 2);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
    }
  }
  THEN(
    "Method 5 should take a pointer to "
    "GenericClass$GenericInnerClass$DoublyNestedInnerClass")
  {
    const std::string func_name = ".method5";
    const std::string func_descriptor =
      ":(LGenericClass$GenericInnerClass$DoublyNestedInnerClass;)V";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    const auto param_type =
      require_type::require_parameter(function_call, "input");
    require_type::require_pointer(
      param_type.type(),
      symbol_typet(
        "java::GenericClass$GenericInnerClass$DoublyNestedInnerClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(param_type.type()));
      const auto &generic_variables =
        to_java_generic_type(param_type.type()).generic_type_variables();
      REQUIRE(generic_variables.size() == 2);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_inst_parameter(generic_param));
        REQUIRE(
          generic_param ==
          java_generic_inst_parametert(symbol_typet("java::Foo")));
      }
    }
  }
  THEN(
    "Method 6 should take a pointer to "
    "GenericClass$GenericInnerClass$DoublyNestedInnerClass")
  {
    const std::string func_name = ".method6";
    const std::string func_descriptor =
      ":(LGenericClass$GenericInnerClass$DoublyNestedInnerClass;)V";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    const auto param_type =
      require_type::require_parameter(function_call, "input");
    require_type::require_pointer(
      param_type.type(),
      symbol_typet(
        "java::GenericClass$GenericInnerClass$DoublyNestedInnerClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(param_type.type()));
      const auto &generic_variables =
        to_java_generic_type(param_type.type()).generic_type_variables();
      REQUIRE(generic_variables.size() == 2);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
    }
  }
  THEN(
    "Method 7 should take a pointer to "
    "GenericClass$GenericInnerClass$DoublyNestedInnerGenericClass")
  {
    const std::string func_name = ".method7";
    const std::string func_descriptor =
      ":(LGenericClass$GenericInnerClass$DoublyNestedInnerGenericClass;)V";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    const auto param_type =
      require_type::require_parameter(function_call, "input");
    require_type::require_pointer(
      param_type.type(),
      symbol_typet(
        "java::GenericClass$GenericInnerClass$"
        "DoublyNestedInnerGenericClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(param_type.type()));
      const auto &generic_variables =
        to_java_generic_type(param_type.type()).generic_type_variables();
      REQUIRE(generic_variables.size() == 3);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_inst_parameter(generic_param));
        REQUIRE(
          generic_param ==
          java_generic_inst_parametert(symbol_typet("java::Foo")));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[2];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param ==
          java_generic_inst_parametert(symbol_typet("java::Foo")));
      }
    }
  }
  THEN(
    "Method 8 should take a pointer to "
    "GenericClass$GenericInnerClass$DoublyNestedInnerGenericClass")
  {
    const std::string func_name = ".method8";
    const std::string func_descriptor =
      ":(LGenericClass$GenericInnerClass$DoublyNestedInnerGenericClass;)V";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    const auto param_type =
      require_type::require_parameter(function_call, "input");
    require_type::require_pointer(
      param_type.type(),
      symbol_typet(
        "java::GenericClass$GenericInnerClass$"
        "DoublyNestedInnerGenericClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(param_type.type()));
      const auto &generic_variables =
        to_java_generic_type(param_type.type()).generic_type_variables();
      REQUIRE(generic_variables.size() == 3);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[2];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
    }
  }
  THEN("Ret Method 1 should return a GenericClass$InnerClass")
  {
    const std::string func_name = ".ret_method1";
    const std::string func_descriptor = ":()LGenericClass$InnerClass;";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    require_type::require_pointer(
      function_call.return_type(),
      symbol_typet("java::GenericClass$InnerClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(function_call.return_type()));
      const auto &generic_variables =
        to_java_generic_type(function_call.return_type())
          .generic_type_variables();
      REQUIRE(generic_variables.size() == 1);
      const java_generic_parametert &generic_param = generic_variables[0];
      REQUIRE(
        generic_param.type_variable() == symbol_typet("java::GenericClass::T"));
    }
  }
  THEN("Ret method 2 should return a GenericClass$GenericInnerClass")
  {
    const std::string func_name = ".ret_method2";
    const std::string func_descriptor = ":()LGenericClass$GenericInnerClass;";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    require_type::require_pointer(
      function_call.return_type(),
      symbol_typet("java::GenericClass$GenericInnerClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(function_call.return_type()));
      const auto &generic_variables =
        to_java_generic_type(function_call.return_type())
          .generic_type_variables();
      REQUIRE(generic_variables.size() == 2);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_inst_parameter(generic_param));
        REQUIRE(
          generic_param ==
          java_generic_inst_parametert(symbol_typet("java::Foo")));
      }
    }
  }
  THEN("Ret method 3 should return a GenericClass$GenericInnerClass")
  {
    const std::string func_name = ".ret_method3";
    const std::string func_descriptor = ":()LGenericClass$GenericInnerClass;";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    require_type::require_pointer(
      function_call.return_type(),
      symbol_typet("java::GenericClass$GenericInnerClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(function_call.return_type()));
      const auto &generic_variables =
        to_java_generic_type(function_call.return_type())
          .generic_type_variables();
      REQUIRE(generic_variables.size() == 2);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
    }
  }
  THEN(
    "Ret method 4 should return a "
    "GenericClass$GenericInnerClass$DoublyNestedInnerClass")
  {
    const std::string func_name = ".ret_method4";
    const std::string func_descriptor =
      ":()LGenericClass$GenericInnerClass$DoublyNestedInnerClass;";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    require_type::require_pointer(
      function_call.return_type(),
      symbol_typet(
        "java::GenericClass$GenericInnerClass$DoublyNestedInnerClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(function_call.return_type()));
      const auto &generic_variables =
        to_java_generic_type(function_call.return_type())
          .generic_type_variables();
      REQUIRE(generic_variables.size() == 2);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_inst_parameter(generic_param));
        REQUIRE(
          generic_param ==
          java_generic_inst_parametert(symbol_typet("java::Foo")));
      }
    }
  }
  THEN(
    "Ret method 5 should return a "
    "GenericClass$GenericInnerClass$DoublyNestedInnerClass")
  {
    const std::string func_name = ".ret_method5";
    const std::string func_descriptor =
      ":()LGenericClass$GenericInnerClass$DoublyNestedInnerClass;";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    require_type::require_pointer(
      function_call.return_type(),
      symbol_typet(
        "java::GenericClass$GenericInnerClass$DoublyNestedInnerClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(function_call.return_type()));
      const auto &generic_variables =
        to_java_generic_type(function_call.return_type())
          .generic_type_variables();
      REQUIRE(generic_variables.size() == 2);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
    }
  }
  THEN(
    "Ret method 6 should return a "
    "GenericClass$GenericInnerClass$DoublyNestedInnerGenericClass")
  {
    const std::string func_name = ".ret_method6";
    const std::string func_descriptor =
      ":()LGenericClass$GenericInnerClass$DoublyNestedInnerGenericClass;";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    require_type::require_pointer(
      function_call.return_type(),
      symbol_typet(
        "java::GenericClass$GenericInnerClass$"
        "DoublyNestedInnerGenericClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(function_call.return_type()));
      const auto &generic_variables =
        to_java_generic_type(function_call.return_type())
          .generic_type_variables();
      REQUIRE(generic_variables.size() == 3);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_inst_parameter(generic_param));
        REQUIRE(
          generic_param ==
          java_generic_inst_parametert(symbol_typet("java::Foo")));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[2];
        REQUIRE(is_java_generic_inst_parameter(generic_param));
        REQUIRE(
          generic_param ==
          java_generic_inst_parametert(symbol_typet("java::Foo")));
      }
    }
  }
  THEN(
    "Ret method 7 should return a "
    "GenericClass$GenericInnerClass$DoublyNestedInnerGenericClass")
  {
    const std::string func_name = ".ret_method7";
    const std::string func_descriptor =
      ":()LGenericClass$GenericInnerClass$DoublyNestedInnerGenericClass;";
    const std::string process_func_name =
      class_prefix + func_name + func_descriptor;

    REQUIRE(new_symbol_table.has_symbol(process_func_name));
    const symbolt &function_symbol =
      new_symbol_table.lookup_ref(process_func_name);

    const code_typet &function_call =
      require_type::require_code(function_symbol.type);

    require_type::require_pointer(
      function_call.return_type(),
      symbol_typet(
        "java::GenericClass$GenericInnerClass$"
        "DoublyNestedInnerGenericClass"));

    THEN("The pointer should be generic")
    {
      REQUIRE(is_java_generic_type(function_call.return_type()));
      const auto &generic_variables =
        to_java_generic_type(function_call.return_type())
          .generic_type_variables();
      REQUIRE(generic_variables.size() == 3);
      {
        const java_generic_parametert &generic_param = generic_variables[0];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[1];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
      {
        const java_generic_parametert &generic_param = generic_variables[2];
        REQUIRE(is_java_generic_parameter(generic_param));
        REQUIRE(
          generic_param.type_variable() ==
          symbol_typet("java::GenericClass::T"));
      }
    }
  }
}
