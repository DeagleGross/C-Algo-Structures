//#include <iostream>
//#include <fstream>
//#include <cstdlib>
//#include <vector>
//#include <string>
//
//using namespace std;
//
//string s;
//size_t l = 0;
//size_t M, N, K;
//
//fstream fin("input.txt", ios::in);
//fstream fout("output.txt", ios::out);
//
//pair<size_t, size_t> getLeftAns(size_t left, size_t count) {
//    size_t ans = 1;
//
//    for (size_t i = 0; i < count; ++i) {
//        size_t last_ans = ans;
//        ans *= left;
//
//        if (last_ans != ans / left)
//            return make_pair(last_ans, i);
//    }
//
//    return make_pair(ans, count);
//}
//
//void writeNum(size_t number) {
//    if (++l == M)
//        fout << number;
//    else
//        fout << number << " ";
//}
//
////Необходимо реализовать данный метод
////Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
//static string get(size_t n, size_t k, size_t m)
//{
//
//    --k;
//
//    pair<size_t, size_t > p = getNotOverflowedValues(n, m);
//    size_t a = p.first;
//    size_t b = p.second;
//
//
//    /*
//     * already writing a lot of numbers that couldn't be reached
//     * because of overflow
//     */
//    for (int i = 0; i < (int)m - (int)p.second - 1; ++i) {
//        if (i == -1)
//            continue;
//        writeNum(1);
//    }
//
//    size_t left_ans = p.first;
//
//    for (int i = (int)m - (int)p.second - 1; i < (int)m; ++i) {
//        if (i == -1)
//            continue;
//
//        if (p.second == m)
//            left_ans /= n;
//
//        size_t index = (left_ans == 0) ? n : k / left_ans;
//        writeNum(index + 1);
//
//        k -= index * left_ans;
//
//        if (p.second != m)
//            left_ans /= n;
//
//    }
//
//    return s;
//}
//
////int main()
////{
////
////    fin >> N >> M >> K;
////
////    get(N, K, M);
////    fout << "\n";
////}