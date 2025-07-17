flex main->int {
	flexvar:int a = 10, int:b = 10, int:sum = a + b;
	flex::write(stdout, f"{a} + {b} = {sum}");
	ret 0;
}
