#include <vector>
#include <string>

class FormatVisitor: public BaseVisitor {
 public:
    void Visit(const BaseNode* node) override {
        node->Visit(this);
    }

    void Visit(const ClassDeclarationNode* node) override {
        formatted_code.push_back(tab + "class " + node->ClassName() + " {");

        if (!node->PublicFields().empty()) {
            formatted_code.push_back(tab + "  public:");
            tab += "    ";
            for (size_t i = 0; i < node->PublicFields().size(); i++) {
                node->PublicFields()[i]->Visit(this);
                formatted_code[formatted_code.size() - 1] += ";";
            }
            tab = tab.substr(0, tab.size() - 4);
        }
        if (!node->ProtectedFields().empty()) {
            formatted_code.push_back("");
            formatted_code.push_back(tab + "  protected:");
            tab += "    ";
            for (size_t i = 0; i < node->ProtectedFields().size(); i++) {
                node->ProtectedFields()[i]->Visit(this);
                formatted_code[formatted_code.size() - 1] += ";";
            }
            tab = tab.substr(0, tab.size() - 4);
        }
        if (!node->PrivateFields().empty()) {
            formatted_code.push_back("");
            formatted_code.push_back(tab + "  private:");
            tab += "    ";
            for (size_t i = 0; i < node->PrivateFields().size(); i++) {
                node->PrivateFields()[i]->Visit(this);
                formatted_code[formatted_code.size() - 1] += ";";
            }
            tab = tab.substr(0, tab.size() - 4);
        }
        formatted_code.push_back(tab + "}");
        if (tab == "") {
            formatted_code[formatted_code.size() - 1] += ";";
        }
    }
    void Visit(const VarDeclarationNode* node) override {
        formatted_code.push_back(tab + node->TypeName() \
                                    + " " + node->VarName());
    }
    void Visit(const MethodDeclarationNode* node) override {
        formatted_code.push_back(tab + node->ReturnTypeName() + " " \
                                    + node->MethodName() + "(");
        for (size_t i = 0; i < node->Arguments().size(); i++) {
            Visit(node->Arguments()[i]);
            formatted_code[formatted_code.size() - 2] +=
                    formatted_code[formatted_code.size() - 1]\
                                    .substr(tab.size());

            if (i < node->Arguments().size() - 1) {
                formatted_code[formatted_code.size() - 2] += ", ";
            }
            formatted_code.pop_back();
        }
        formatted_code[formatted_code.size() - 1] += ")";
    }

    const std::vector<std::string>& GetFormattedCode() const {
        return formatted_code;
    }


 private:
    std::string tab = "";
    std::vector<std::string> formatted_code;
};
