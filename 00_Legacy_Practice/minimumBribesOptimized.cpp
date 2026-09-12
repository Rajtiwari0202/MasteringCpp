
def minimumBribes(q):
    b = 0
    for i in range(len(q)):
        if q[i] - (i + 1) > 2:
            print("Too chaotic")
            return 0

        for j in range(max(0, q[i] - 2), i):
            if q[j] > q[i]:
                b += 1

    print(b)
    return 0