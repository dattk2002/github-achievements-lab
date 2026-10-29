mod solution;

use solution::daily_temperatures;

fn oracle(temperatures: &[i32]) -> Vec<usize> {
    (0..temperatures.len())
        .map(|i| {
            (i + 1..temperatures.len())
                .find(|&j| temperatures[j] > temperatures[i])
                .map_or(0, |j| j - i)
        })
        .collect()
}

#[test]
fn finds_the_nearest_strictly_warmer_day() {
    assert_eq!(daily_temperatures(&[65, 64, 64, 68, 63, 70]), vec![3, 2, 1, 2, 1, 0]);
    assert_eq!(daily_temperatures(&[30, 30, 31]), vec![2, 1, 0]);
}

#[test]
fn handles_empty_singleton_and_monotone_inputs() {
    assert_eq!(daily_temperatures(&[]), Vec::<usize>::new());
    assert_eq!(daily_temperatures(&[50]), vec![0]);
    assert_eq!(daily_temperatures(&[31, 42, 60, 100]), vec![1, 1, 1, 0]);
    assert_eq!(daily_temperatures(&[80, 70, 60, 50]), vec![0, 0, 0, 0]);
    assert_eq!(daily_temperatures(&[50, 50, 50]), vec![0, 0, 0]);
}

#[test]
fn comparison_needs_no_temperature_arithmetic() {
    // The borrowed-slice helper also supports values outside LeetCode's range.
    assert_eq!(daily_temperatures(&[i32::MIN, i32::MAX, i32::MIN]), vec![1, 0, 0]);
}

#[test]
fn agrees_with_quadratic_oracle_for_seeded_random_inputs() {
    let mut state = 739_u64;
    let mut next = || {
        state = state.wrapping_mul(6364136223846793005).wrapping_add(1);
        (state >> 32) as u32
    };
    for _ in 0..1000 {
        let n = (next() % 81) as usize;
        let input: Vec<i32> = (0..n).map(|_| 30 + (next() % 71) as i32).collect();
        assert_eq!(daily_temperatures(&input), oracle(&input), "input: {input:?}");
    }
}

#[test]
fn handles_one_hundred_thousand_days_and_long_waits() {
    let mut input = vec![50; 100_000];
    let waits = daily_temperatures(&input);
    assert_eq!(waits.len(), input.len());
    assert!(waits.iter().all(|&wait| wait == 0));
    input[99_999] = 100;
    let waits = daily_temperatures(&input);
    assert_eq!(waits.len(), input.len());
    for (day, &wait) in waits.iter().enumerate() {
        assert_eq!(wait, 99_999 - day, "day {day}");
    }
    assert_eq!(input[0], 50);
    assert_eq!(input[99_999], 100);
}
