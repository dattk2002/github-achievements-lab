export function lengthOfLongestSubstring(s: string): number {
  const lastSeen = new Map<string, number>();
  let left = 0;
  let right = 0;
  let best = 0;
  // for...of advances by Unicode code point, not UTF-16 code unit.
  for (const character of s) {
    const previous = lastSeen.get(character);
    if (previous !== undefined) left = Math.max(left, previous + 1);
    lastSeen.set(character, right);
    best = Math.max(best, right - left + 1);
    right++;
  }
  return best;
}
