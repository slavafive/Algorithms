def is_palindrom(str):
    answer = True
    i, j = 0, len(str) - 1
    while i < j:
        if str[i] == str[j]:
            i += 1
            j -= 1
        else:
            answer = False
            break
    return answer


def find_longest_prefix_palindrom(str):
    i = 1
    max_palindrom_i = i
    while i <= len(str):
        if is_palindrom(str[0:i]):
            max_palindrom_i = i
        i += 1
    return max_palindrom_i


n = int(input())
for i in range(n):
    print(find_longest_prefix_palindrom(input()))