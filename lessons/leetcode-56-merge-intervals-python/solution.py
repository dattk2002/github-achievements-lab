def merge_intervals(intervals: list[list[int]]) -> list[list[int]]:
    """Merge closed integer intervals without changing or aliasing the input.

    Each input row must contain exactly two integers, start <= end.
    """
    merged: list[list[int]] = []
    for start, end in sorted(intervals):
        if not merged or start > merged[-1][1]:
            merged.append([start, end])
        else:
            merged[-1][1] = max(merged[-1][1], end)
    return merged
