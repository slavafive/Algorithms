def get_answer(str, pattern):
    answer = 0
    for i in range(len(str)):
        for j in range(i + 1, len(str) + 1):
            if not (pattern in str[i:j]):
                answer += 1
    return answer


n = int(input())
for i in range(n):
    print(get_answer(input(), input()))