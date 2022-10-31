#ifndef PARSETREE_H
#define PARSETREE_H

#include <string>
#include <vector>

class ParseTree {
    private:
        std::string type;
        std::string value;
        std::vector<ParseTree*> children;

    public:
        ParseTree(std::string type, std::string value);

        void addChild(ParseTree* child);

        std::vector<ParseTree*> getChildren();

        std::string getType();

        std::string getValue();

        std::string tostring();

        std::string tostring(int depth);
};

#endif /*PARSETREE_H*/