use std::collections::HashSet;

pub fn longest_consecutive(nums: &[i32]) -> usize {
    let values: HashSet<i32> = nums.iter().copied().collect();
    let mut best = 0;
    for &start in &values {
        if start.checked_sub(1).map_or(false, |previous| values.contains(&previous)) {
            continue;
        }
        let mut length = 1;
        let mut current = start;
        while let Some(next) = current.checked_add(1) {
            if !values.contains(&next) {
                break;
            }
            length += 1;
            current = next;
        }
        best = best.max(length);
    }
    best
}
