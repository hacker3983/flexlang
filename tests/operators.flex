flex main -> int {
	int a = 10, b = 20;
	flex::write(stdout, "\033[21mLess than\033[24m");	
	flex::write(stdout, f"{a} < {b} = {a < b}");
	flex::write(stdout, "\033[21mGreater than\033[24m");
	flex::write(stdout, f"{a} > {b} = {a > b}");
	flex::write(stdout, "\033[21mLess than or equal to\033[24m");
	flex::write(stdout, "{a} <= {b} = {a <= b}");
	flex::write(stdout, "\033[21mGreater than or equal to\033[24m");
	flex::write(stdout, "{a} >= {b} = {a >= b}");
	flex::write(stdout, "\033[21mComparison equal\033[24m");
	flex::write(stdout, f"{a} == {b} = {a == b}");
	flex::write(stdout, "\033[21mBitwise exclusive or:\033[24m");
	flex::write(stdout, f"{a} ^ {b} = {a ^ b}");
	flex::write(stdout, "\033[21mBitwise Or:\033[24m");
	flex::write(stdout, f"{a} | {b} = {a | b}");
	flex::write(stdout, "\033[21mBitwise And:\033[24m");
	flex::write(stdout, f"{a} & {b} = {a & b}");
	flex::write(stdout, "\033[21mAddition:\033[24m");
	flex::write(stdout, f"{a} + {b} = {a + b}");
	flex::write(stdout, "\033[22mSubtraction:\033[24m");
	flex::write(stdout, f"{a} - {b} = {a - b}");
	flex::write(stdout, "\033[22mDivision:\033[24m");
	flex::write(stdout, f"{a} / {b} = {a / b}");
	flex::write(stdout, "\033[22mMultiplication\033[24m");
	flex::write(stdout, f"{a} * {b} = {a * b}");
	ret 0;
}
