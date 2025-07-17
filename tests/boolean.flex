flex check_requirements int age -> bool {
	ret (age >= 18) ? true : false;
}

flex main -> int {
	// Testing out booleans in flex
	flexvar int:age = flex::input("How old are you? "),
		bool:drink = check_requirements(age);
	if(drink) {
		flex::write(stdout, "You are old enough to drink!");
	} else {
		flex::write(stdout, "You are too young to drink!");
	}
	true; false; true; false;
	ret 0;
}
