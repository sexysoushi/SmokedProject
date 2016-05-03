#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <vector>
#include <stdexcept>

using namespace std;

template<typename T> class MatrixStack {
private:
    vector<T> stack;
public:

    MatrixStack() {}

    size_t size() const {
        return stack.size();
    }

    void push(const T& mat) {
        if(size() > 0) {
            T top = stack.back();
            stack.push_back(top * mat);
        } else {
            stack.push_back(mat);
        }
    }

    bool isEmpty() const {
        return stack.size() == 0;
    }

    T top() const {
        if(size() > 0) {
            return stack.back();
        } else {
            throw logic_error("the stack is empty");
        }
    }

    T pop() {
        if(size() > 0) {
            T tmp = stack.back();
            stack.pop_back();
            return tmp;
        } else {
            throw logic_error("the stack is empty");
        }
    }
};

#endif // MATRIXSTACK_H
