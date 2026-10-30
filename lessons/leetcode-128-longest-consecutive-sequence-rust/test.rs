mod solution;
use solution::longest_consecutive;

fn oracle(nums: &[i32]) -> usize {
    let mut sorted = nums.to_vec();
    sorted.sort_unstable();
    sorted.dedup();
    let mut best = 0;
    let mut run = 0;
    let mut previous: Option<i32> = None;
    for value in sorted {
        run = if previous.map(|p| i64::from(value) - i64::from(p)) == Some(1) {
            run + 1
        } else {
            1
        };
        best = best.max(run);
        previous = Some(value);
    }
    best
}

#[test]
fn unsorted_runs_duplicates_negatives_and_empty_input() {
    assert_eq!(longest_consecutive(&[9, 5, 7, 6, 6, -2, -1, 0]), 3);
    assert_eq!(longest_consecutive(&[5, 5, 5]), 1);
    assert_eq!(longest_consecutive(&[]), 0);
    assert_eq!(longest_consecutive(&[12]), 1);
    assert_eq!(longest_consecutive(&[5, 2, 4, 1, 3]), 5);
}

#[test]
fn integer_extremes_do_not_overflow_or_wrap_into_a_single_run() {
    assert_eq!(longest_consecutive(&[i32::MIN, i32::MIN + 1, i32::MAX]), 2);
    assert_eq!(longest_consecutive(&[i32::MAX - 1, i32::MAX]), 2);
    assert_eq!(longest_consecutive(&[i32::MIN, i32::MAX]), 1);
}

#[test]
fn agrees_with_sorted_oracle_on_one_thousand_seeded_inputs() {
    let mut state = 128_u64;
    let mut next = || {
        state = state.wrapping_mul(6364136223846793005).wrapping_add(1);
        (state >> 32) as u32
    };
    for _ in 0..1000 {
        let n = (next() % 100) as usize;
        let input: Vec<i32> = (0..n).map(|_| (next() % 101) as i32 - 50).collect();
        assert_eq!(longest_consecutive(&input), oracle(&input), "input: {input:?}");
    }
}

#[test]
fn long_run_and_repeated_values_do_not_restart_scans() {
    let descending: Vec<i32> = (0..100_000).rev().collect();
    assert_eq!(longest_consecutive(&descending), 100_000);
    let mut repeated = vec![0; 50_000];
    repeated.extend(1..=50_000);
    assert_eq!(longest_consecutive(&repeated), 50_001);
}
