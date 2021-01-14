def z_function(str):
    l = r = 0
    n = len(str)
    z = [0] * n
    for i in range(len(str)):
        if r >= i:
            z[i] = min(z[i - l], r - i + 1)
        while z[i] + i < n and str[z[i]] == str[z[i] + i]:
            z[i] += 1
        if i + z[i] - 1 > r:
            l = i
            r = i + z[i] - 1
    z[0] = 0
    return z


s = input()
z = z_function(s)
print(" ".join(map(str, z)))
