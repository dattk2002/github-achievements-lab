def coin_change(coins: list[int], amount: int) -> int:
    """Fewest reusable positive denominations to total a nonnegative amount."""
    usable = sorted({coin for coin in coins if coin <= amount})
    unreachable = amount + 1
    dp = [0] + [unreachable] * amount
    for value in range(1, amount + 1):
        for coin in usable:
            if coin > value:
                break
            dp[value] = min(dp[value], dp[value - coin] + 1)
    return -1 if dp[amount] == unreachable else dp[amount]
