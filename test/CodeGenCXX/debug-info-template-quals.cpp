// RUN: %clang_cc1 -emit-llvm -g -triple x86_64-apple-darwin %s -o - | FileCheck %s

template<typename _CharT>
struct basic_string {

  basic_string&
  assign(const _CharT* __s, const basic_string<_CharT> &x)
  {
    return *this;
  }
};

void foo (const char *c) {
  basic_string<char> str;
  str.assign(c, str);
}

// CHECK: [[BS:.*]] = !MDCompositeType(tag: DW_TAG_structure_type, name: "basic_string<char>"
// CHECK-SAME:                         line: 4
// CHECK-SAME:                         size: 8, align: 8
// CHECK: [[TYPE:![0-9]*]] = !MDSubroutineType(types: [[ARGS:.*]])
// CHECK: [[ARGS]] = !{!{{.*}}, !{{.*}}, [[P:![0-9]*]], [[R:.*]]}
// CHECK: [[P]] = !MDDerivedType(tag: DW_TAG_pointer_type, baseType: [[CON:![0-9]*]]
// CHECK: [[CON]] = !MDDerivedType(tag: DW_TAG_const_type, baseType: [[CH:![0-9]*]]
// CHECK: [[CH]] = !MDBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)

// CHECK: [[R]] = !MDDerivedType(tag: DW_TAG_reference_type, baseType: [[CON2:![0-9]*]]
// CHECK: [[CON2]] = !MDDerivedType(tag: DW_TAG_const_type, baseType: !"_ZTS12basic_stringIcE"
// CHECK: !MDSubprogram(name: "assign"
// CHECK-SAME:          line: 7
// CHECK-SAME:          scopeLine: 8
