flex main -> int {
	flexvar:string name;
	name = flex::input(stdin, "Please enter your name: ");
	flex::write(stdout, f"Nice to meet you {name}. Welcome to flexlang!");
	ret 0;
}
