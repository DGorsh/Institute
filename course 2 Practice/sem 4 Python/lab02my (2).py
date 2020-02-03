import numpy as np


def GCD(first: int, second: int):
    """Iterative  Greatest Common Divisor for number"""
    x, xt, y, yt = 1, 0, 0, 1
    while second:
        q = first // second
        first, second = second, first % second
        x, xt = xt, x - xt * q
        y, yt = yt, y - yt * q
    return first, x, y


def InverseMod(a: int, n: int):
    d, x, y = GCD(a, n)
    if d != 1:
        return None
    else:
        return x % n


def IntKaratsuba(a: int, b: int):
    minus = int(a) * int(b) < 0

    a = abs(int(a))
    b = abs(int(b))

    if a < 10 and b < 10:
        return a * b

    a, b = str(a), str(b)
    l_a, l_b = len(a), len(b)

    if l_a < l_b:
        b, a = a, b
        l_b, l_a = l_a, l_b

    if l_a & 1:
        a = '0' + a
        l_a += 1

    while l_a != l_b:
        b = '0' + b
        l_b += 1

    n = l_a // 2

    a1, a2 = a[:n], a[n:]
    b1, b2 = b[:n], b[n:]

    f = IntKaratsuba(a1, b1)
    s = IntKaratsuba(a2, b2)
    m = IntKaratsuba(int(a1) + int(a2), int(b1) + int(b2))

    res = f * 10 ** (2 * n) + (m - f - s) * 10 ** n + s
    return -res if minus else res


def PolyKaratsuba(a, b):
    if a.shape[0] == 1 and b.shape[0] == 1:
        return a * b

    l_a, l_b = len(a), len(b)

    if l_a < l_b:
        a, b = b, a
        l_a, l_b = l_b, l_a

    if l_a & 1:
        l_a += 1
        a = np.concatenate([np.zeros(1), a])

    if l_b != l_a:
        b = np.concatenate([np.zeros(l_a - l_b), b])

    n = l_a // 2

    a1, a2 = a[:n], a[n:]
    b1, b2 = b[:n], b[n:]

    f = PolyKaratsuba(a1, b1)
    s = PolyKaratsuba(a2, b2)
    m = PolyKaratsuba(np.polyadd(a1, a2), np.polyadd(b1, b2))
    m = np.polysub(np.polysub(m, f), s)

    f = np.concatenate([f, np.zeros(2 * n)])
    m = np.concatenate([m, np.zeros(n)])

    res = np.polyadd(np.polyadd(f, m), s)

    i = 0
    for i in range(0, len(res)):
        if res[i]:
            break

    return res[i:]


def BinPowMod(a: int, deg: int, n: int):
    if n == 0:
        raise ValueError("n = 0")

    a %= n

    if a == 0:
        return 0 if deg else None

    if deg < 0:
        a = InverseMod(a, n)
        if a is None:
            return None
        deg *= -1

    res = 1

    while deg:
        if deg & 1:
            res *= a
            res %= n
        a *= a
        a %= n
        deg >>= 1

    return res
