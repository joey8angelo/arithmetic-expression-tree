#include "arithmeticExpression.h"
#include <stack>
#include <sstream>
#include <fstream>

arithmeticExpression::arithmeticExpression(const string& s) : infixExpression(s), root(nullptr) {}

arithmeticExpression::~arithmeticExpression() {
    removeAll(root);
}

void arithmeticExpression::removeAll(TreeNode* curr) {
    if (curr == nullptr)
        return;
    else {
        removeAll(curr->left);
        removeAll(curr->right);
        delete curr;
    }
}

void arithmeticExpression::buildTree() {
    stack<TreeNode*> s;
    string post = infix_to_postfix();
    TreeNode* temp;
    TreeNode* r;
    TreeNode* l;
    
    for (int i = 0; i < static_cast<int>(post.size()); i++) {
        temp = nullptr;
        l = nullptr;
        r = nullptr;
        switch (post[i]) {
        case '*':
        {
            r = s.top();
            s.pop();
            l = s.top();
            s.pop();
            s.push(new TreeNode('*', i + 97));
            temp = s.top();
            temp->left = l;
            temp->right = r;
        }
            break;
        case '+':
        {
            r = s.top();
            s.pop();
            l = s.top();
            s.pop();
            s.push(new TreeNode('+', i + 97));
            temp = s.top();
            temp->left = l;
            temp->right = r;
        }
            break;
        case '-':
        {
            r = s.top();
            s.pop();
            l = s.top();
            s.pop();
            s.push(new TreeNode('-', i + 97));
            temp = s.top();
            temp->left = l;
            temp->right = r;
        }
            break;
        case '/':
        {
            r = s.top();
            s.pop();
            l = s.top();
            s.pop();
            s.push(new TreeNode('/', i + 97));
            temp = s.top();
            temp->left = l;
            temp->right = r;
        }
            break;
        default:
            s.push(new TreeNode(post[i], i + 97));
            break;
        }
    }
    root = s.top();
}

void arithmeticExpression::infix() {
    infix(root);
}

void arithmeticExpression::infix(TreeNode* node) {
    if (node == nullptr)
        return;
    else {
        if (!(node->left == nullptr && node->right == nullptr))
            cout << "(";
        
        infix(node->left);
        cout << node->data;
        infix(node->right);
        
        if (!(node->left == nullptr && node->right == nullptr))
            cout << ")";
    }
}

void arithmeticExpression::prefix() {
    prefix(root);
}

void arithmeticExpression::prefix(TreeNode* node) {
    if (node == nullptr)
        return;
    else {
        cout << node->data;
        prefix(node->left);
        prefix(node->right);
    }
}

void arithmeticExpression::postfix() {
    postfix(root);
}

void arithmeticExpression::postfix(TreeNode* node) {
    if (node == nullptr)
        return;
    else {
        postfix(node->left);
        postfix(node->right);
        cout << node->data;
    }
}

int arithmeticExpression::evaluate() {
    if (!isValidIntegerExpression(root)) {
        throw std::logic_error("expression not valid");
    }
    return evaluateIntegerExpression(root);
}

int arithmeticExpression::evaluateIntegerExpression(TreeNode* node) {
    if (node->left == nullptr && node->right == nullptr)
        return node->data - 48;
    
    else {
        switch (node->data) {
        case '+':
            return evaluateIntegerExpression(node->left) + evaluateIntegerExpression(node->right);
            break;
        case '-':
            return evaluateIntegerExpression(node->left) - evaluateIntegerExpression(node->right);
            break;
        case '*':
            return evaluateIntegerExpression(node->left) * evaluateIntegerExpression(node->right);
            break;
        case '/':
            return evaluateIntegerExpression(node->left) + evaluateIntegerExpression(node->right);
            break;
        }
    }
    return -1;
}

bool arithmeticExpression::isValidIntegerExpression(TreeNode* node) {
    if (node->left == nullptr && node->right == nullptr) {
        if (node->data >= 48 && node->data <= 57)
            return true;
        else
            return false;
    }
    else {
        bool L = isValidIntegerExpression(node->left);
        bool R = isValidIntegerExpression(node->right);

        if (L == true && R == true)
            return true;
        else
            return false;
    }
}
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}