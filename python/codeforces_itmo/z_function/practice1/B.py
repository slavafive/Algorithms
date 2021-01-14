def is_prefix(pattern, str):
    return pattern == str[0:len(pattern)]


def is_suffix(pattern, str):
    return pattern == str[len(str) - len(pattern):len(str)]


def get_answer(str):
    answer = 0
    for i in range(len(str)):
        for j in range(i + 1, len(str) + 1):
            pattern = str[i:j]
            if is_prefix(pattern, str) != is_suffix(pattern, str):
                answer += 1
    return answer


n = int(input())
for i in range(n):
    print(get_answer(input()))