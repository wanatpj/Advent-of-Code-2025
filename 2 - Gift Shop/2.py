proper_divisors = {
    1: [],
    2: [1],
    3: [1],
    4: [1, 2],
    5: [1],
    6: [1, 2, 3],
    7: [1],
    8: [1, 2, 4],
    9: [1, 3],
    10: [1, 2, 5],
}

def invalid(n: int) -> bool:
    n_str = str(n)
    for divisor in proper_divisors[len(n_str)]:
        if n == int(n_str[ : divisor] * (len(n_str) // divisor)):
            return True
    return False

def main():
    ranges = [tuple(map(int, raw_range.split("-"))) for raw_range in input().split(",")]
    total_sum = 0
    for start, end in ranges:
        for i in range(start, end+1):
            if invalid(i):
                total_sum += i
    print(total_sum)

if __name__ == "__main__":
    main()