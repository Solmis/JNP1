#include <iostream>
#include "fun_tree.h"

int main() {
    FunTree<int> bst_tree;
    bst_tree.insert(3);
    bst_tree.insert(5);
    bst_tree.insert(4);
    bst_tree.insert(2);
    bst_tree.insert(1);
    bst_tree.print_mah_tree();
    //std::ostream sssss(NULL);
    //sssss << (FunTree<int>::inorder << bst_tree);
    /*std::cout<<"2";
    ::std::cout << sssss;
    std::cout<<"3";*/
    /*::std::cout << "bst_tree" << ::std::endl
                << FunTree<int>::inorder << bst_tree << ::std::endl;
                << FunTree<int>::preorder << bst_tree << ::std::endl
                << FunTree<int>::postorder << bst_tree << ::std::endl;

    FunTree<int>::Comparator fun_comparator =
        [](int a, int b)->int {
            static int i = 0b0111010;
            i >>= 1;
            return i & 1;
        };
    FunTree<int> fun_tree;
    fun_tree.insert(1, fun_comparator);
    fun_tree.insert(2, fun_comparator);
    fun_tree.insert(3, fun_comparator);
    fun_tree.insert(4, fun_comparator);
    fun_tree.insert(5, fun_comparator);
    ::std::cout << "fun_tree" << ::std::endl
                << FunTree<int>::inorder << fun_tree << ::std::endl
                << FunTree<int>::preorder << fun_tree << ::std::endl
                << FunTree<int>::postorder << fun_tree << ::std::endl;

    ::std::cout << "fun_tree.find(3) = " << fun_tree.find(3) << ::std::endl;
    ::std::cout << "fun_tree.find(5) = " << fun_tree.find(5) << ::std::endl;
*/
    FunTree<int>::Operator fun_printer = [](int e) {
        ::std::cout << e << '$';
    };
    /*
    ::std::cout << "custom print:";
    bst_tree.apply(fun_printer);
    ::std::cout << ::std::endl;

    FunTree<int>::UnaryOperator fun_un_op = [](int e)->int {
        return e - 2;
    };
    FunTree<int> minus_two = bst_tree.map(fun_un_op,
                                          FunTree<int>::preorder,
                                          ::std::greater<int>{});
    ::std::cout << "minus two:"
                << FunTree<int>::inorder << minus_two << ::std::endl;

    FunTree<int>::Predicate fun_predicate = [](int e)->bool {
        return (e & 1) == 1;
    };
    FunTree<int> odd = minus_two.filter(fun_predicate);
    ::std::cout << "odd:" << odd << ::std::endl;

    FunTree<int>::BinaryOperator fun_bin_op = ::std::plus<int>{};
    int sum = bst_tree.fold(fun_bin_op, 0, FunTree<int>::inorder);
    ::std::cout << "sum: " << sum << ::std::endl;

    fun_tree.erase(2, ::std::greater<int>{});
    ::std::cout << "fun_tree:" << fun_tree << ::std::endl;

    FunTree<int> tmp_tree(bst_tree);
    ::std::cout << "tmp_tree:" << tmp_tree << ::std::endl;
    fun_tree = tmp_tree;
    ::std::cout << "fun_tree:" << fun_tree << ::std::endl;

    FunTree<int>::UnaryOperator g = fun_tree.fun(fun_un_op, fun_bin_op);
    ::std::cout << "g(7) = " << g(7) << ::std::endl;*/
}
