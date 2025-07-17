flex add:int a, int b -> int {
        ret a + b;
}

flex main -> int {
	flexvar:int a = flex::input(stdin, "Enter the first number: "),
	int b = flex::input(stdin, "Enter the second number: ");
	flex::write(stdout, f"{a} + {b} = {add(a, b)}");
	ret 0;
}
