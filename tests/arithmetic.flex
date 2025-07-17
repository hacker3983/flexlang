flex main -> int {
	int a = 10, b = 20;
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
