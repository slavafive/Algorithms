def get_answer(k, j):
    if j == 0 or j % 2 == 1:
        return 0
    binary = bin(j // 2)
    binary = binary[2:]
    last_zero_index = binary.rfind('1') + 1
    number_of_zeros_in_the_end = len(binary) - last_zero_index
    return 2 ** (number_of_zeros_in_the_end + 1) - 1


n = int(input())
for i in range(n):
    k, j = map(int, input().split())
    print(get_answer(k, j))


'''
a
0
aba
001
0 + 0 + 1
abacaba
0010301
0 + 01 + 0 + 3 + 01
abacabadabacaba
001030107010301
0 + 010301 + 0 + 7 + 010301
abacabadabacabaeabacabadabacaba
0010301070103010.15.010301070103010
0 + 01030107010301 + 0 + 15 + 01030107010301
k = 2 -> 1 -> 0001 -> 1
k = 4 -> 2 -> 0010 -> 3
k = 6 -> 3 -> 0011 -> 1
k = 8 -> 4 -> 0100 -> 7
k = 10 -> 5 -> 0101 -> 1
k = 12 -> 6 -> 0110 -> 3
k = 14 -> 7 -> 0111 -> 1
k = 16 -> 8 -> 1000 -> 15
k = 18 -> 9 -> 1001 -> 1
k = 20 -> 10 -> 1010 -> 3
k = 22 -> 11 -> 1011 -> 1
k = 24 -> 12 -> 1100 -> 7
2 ** (number_of_zeros_in_the_end + 1) - 1
'''