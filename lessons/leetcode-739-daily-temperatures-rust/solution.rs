pub fn daily_temperatures(temperatures: &[i32]) -> Vec<usize> {
    let mut answer = vec![0; temperatures.len()];
    let mut pending: Vec<usize> = Vec::new();
    for (today, &temperature) in temperatures.iter().enumerate() {
        while let Some(&day) = pending.last() {
            if temperature <= temperatures[day] {
                break;
            }
            answer[day] = today - day;
            pending.pop();
        }
        pending.push(today);
    }
    answer
}
