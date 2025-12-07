def sum_range(a: int, b: int, l: int) -> int:
    return (a + b) * (b - a + 1) // 2 * (10 ** l + 1)

def sum_all(n: int) -> int:
    total_sum = 0
    i = 0
    while (10 ** i) <= n:
        total_sum += sum_range(10 ** i, min(n, 10 ** (i + 1) - 1), i + 1)
        i += 1
    return total_sum

def sum_invalid(n: int) -> int:
    if (x := len(n_str := str(n))) % 2:
        return sum_all(10 ** (x // 2) - 1)
    left, right = n_str[: x // 2], n_str[x // 2 : ]
    return sum_all(int(left) - int(left > right))

def main():
    ranges = sorted([tuple(map(int, raw_range.split("-"))) for raw_range in input().split(",")])
    current_end = 0
    total_sum = 0
    for start, end in ranges:
        if start > current_end:
            total_sum += sum_invalid(current_end) - sum_invalid(start - 1)
        current_end = max(current_end, end)
    total_sum += sum_invalid(current_end)
    print(total_sum)

if __name__ == "__main__":
    main()