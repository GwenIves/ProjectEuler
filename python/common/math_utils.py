def arithmetic_sequence_sum(start, end, step):
    if end <= start:
        return 0

    count = 1 + (end - start - 1) // step
    last = start + (count - 1) * step

    return count * (start + last) // 2

if __name__ == "__main__":
    pass
