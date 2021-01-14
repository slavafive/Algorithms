def is_real_pattern(pattern, str, i):
    answer = True
    for j in range(len(pattern)):
        if not (pattern[j] == '?' or pattern[j] == str[i + j]):
            answer = False
            break
    return answer


def get_answer(str, pattern):
    answer = 0
    answers = []
    for i in range(len(str) - len(pattern) + 1):
        if is_real_pattern(pattern, str, i):
            answer += 1
            answers.append(i)
    return answer, answers


n = int(input())
for i in range(n):
    answer, answers = get_answer(input(), input())
    print(answer)
    print(" ".join(map(str, answers)))