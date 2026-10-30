export function productExceptSelf(nums: readonly number[]): number[] {
  const answer = Array<number>(nums.length);
  let prefix = 1;
  for (let i = 0; i < nums.length; i++) {
    answer[i] = prefix;
    prefix *= nums[i];
  }
  let suffix = 1;
  for (let i = nums.length - 1; i >= 0; i--) {
    const product = answer[i] * suffix;
    answer[i] = product === 0 ? 0 : product; // Normalize JavaScript's -0.
    suffix *= nums[i];
  }
  return answer;
}
