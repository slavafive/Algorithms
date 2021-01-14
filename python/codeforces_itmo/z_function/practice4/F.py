def z_function(s):
    n = len(s)
    z = [0] * n
    l = r = 0
    for i in range(n):
        if i <= r:
            z[i] = min(z[i - l], r - i + 1)
        while i + z[i] < n and s[i + z[i]] == s[z[i]]:
            z[i] += 1
        if i + z[i] - 1 > r:
            l = i
            r = i + z[i] - 1
    z[0] = 0
    return z


def does_first_contain_second(a, b):
    new_string = b + "#" + a
    z = z_function(new_string)
    answer = False
    for i in range(len(b) + 1, len(new_string)):
        if z[i] == len(b):
            answer = True
            break
    return answer


def find_common_part(a, b):
    new_string = a + "#" + b
    z = z_function(new_string)
    for i in range(len(a), len(new_string)):
        if i + z[i] == len(new_string):
            return b + a[z[i]:]
    return b + a


def find_superline(s, t):
    if does_first_contain_second(s, t):
        return s
    if does_first_contain_second(t, s):
        return t
    res1 = find_common_part(s, t)
    res2 = find_common_part(t, s)
    return res1 if len(res1) < len(res2) else res2


n = int(input())
for i in range(n):
    s = input()
    t = input()
    print(find_superline(s, t))
