int foo(void)
{
	int f1, f2, f3, f4, f5, f6;

	f1 = open1();
	if (f1 == -1) {
		goto open1_err;
	}

	f2 = open2();
	if (f2 == -1) {
		goto open2_err;
	}

	f3 = open3();
	if (f3 == -1) {
		goto open3_err;
	}

	f4 = open4();
	if (f4 == -1) {
		goto open4_err;
	}

	f5 = open5();
	if (f5 == -1) {
		goto open5_err;
	}

	...;













	f6 = open6();
	if (f6 == -1) {
		goto open6_err;
	}

	...;





















































	f7 = open7();
	if (f7 == -1) {
		goto open7_err;
	}




	close7();
	close6();
	close5();
	close4();
	close2();
	close1();
	return 0;


	close7();
open7_err:
	close6();
open6_err:
	close5();
open5_err:
	close4();
open4_err:
	close3();
open3_err:
	close2();
open2_err:
	close1();
open1_err:
	return -1;
}
