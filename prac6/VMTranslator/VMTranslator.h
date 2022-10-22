#ifndef VMTRANSLATOR_H
#define VMTRANSLATOR_H

#include <string>

using namespace std;

class VMTranslator {

    public:

        VMTranslator();
        VMTranslator(string moduleName);
        ~VMTranslator();

        static string vm_push(string segment, int offset);
        static string vm_pop(string segment, int offset);

        static string vm_add();
        static string vm_sub();
        static string vm_neg();

        static string vm_eq();
        static string vm_gt();
        static string vm_lt();
        static string vm_and();
        static string vm_or();
        static string vm_not();

        static string vm_label(string label);
        static string vm_goto(string label);
        static string vm_if(string label);

        static string vm_function(string function_name, int n_vars);
        static string vm_call(string function_name, int n_args);
        static string vm_return();

    private:

        static string regDecode(string segment, int offset);
        static string newLabelId();
        static bool validSegment(string segment);
        static string fnLabelEncode(string name);
        static string fnLabelEncode(string modName, string name);
        
        static int labelCount;
        static string moduleName;
        
};

#endif /* VMTRANSLATOR_H */