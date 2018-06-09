#pragma once

namespace ag
{
	/* Represents a keyboard key. */
	class key final
	{
	public:
		static const int a;
		static const int b;
		static const int c;
		static const int d;
		static const int e;
		static const int f;
		static const int g;
		static const int h;
		static const int i;
		static const int j;
		static const int k;
		static const int l;
		static const int m;
		static const int n;
		static const int o;
		static const int p;
		static const int q;
		static const int r;
		static const int s;
		static const int t;
		static const int u;
		static const int v;
		static const int w;
		static const int x;
		static const int y;
		static const int z;
		static const int num_0;
		static const int num_1;
		static const int num_2;
		static const int num_3;
		static const int num_4;
		static const int num_5;
		static const int num_6;
		static const int num_7;
		static const int num_8;
		static const int num_9;
		static const int pad_0;
		static const int pad_1;
		static const int pad_2;
		static const int pad_3;
		static const int pad_4;
		static const int pad_5;
		static const int pad_6;
		static const int pad_7;
		static const int pad_8;
		static const int pad_9;
		static const int f1;
		static const int f2;
		static const int f3;
		static const int f4;
		static const int f5;
		static const int f6;
		static const int f7;
		static const int f8;
		static const int f9;
		static const int f10;
		static const int f11;
		static const int f12;
		static const int escape;
		static const int tilde;
		static const int minus;
		static const int equals;
		static const int backspace;
		static const int tab;
		static const int openbrace;
		static const int closebrace;
		static const int enter;
		static const int semicolon;
		static const int quote;
		static const int backslash;
		static const int backslash2;
		static const int comma;
		static const int fullstop;
		static const int slash;
		static const int space;
		static const int insert;
		static const int del;
		static const int home;
		static const int end;
		static const int pgup;
		static const int pgdn;
		static const int left;
		static const int right;
		static const int up;
		static const int down;
		static const int pad_slash;
		static const int pad_asterisk;
		static const int pad_minus;
		static const int pad_plus;
		static const int pad_delete;
		static const int pad_enter;
		static const int printscreen;
		static const int pause;
		static const int abnt_c1;
		static const int yen;
		static const int kana;
		static const int convert;
		static const int noconvert;
		static const int at;
		static const int circumflex;
		static const int colon2;
		static const int kanji;
		static const int pad_equals;
		static const int backquote;
		static const int semicolon2;
		static const int command;
		static const int back;
		static const int volume_up;
		static const int volume_down;
		static const int search;
		static const int dpad_center;
		static const int button_x;
		static const int button_y;
		static const int dpad_up;
		static const int dpad_down;
		static const int dpad_left;
		static const int dpad_right;
		static const int select;
		static const int start;
		static const int button_l1;
		static const int button_r1;
		static const int button_l2;
		static const int button_r2;
		static const int button_a;
		static const int button_b;
		static const int thumbl;
		static const int thumbr;
		static const int unknown;
		static const int lshift;
		static const int rshift;
		static const int lctrl;
		static const int rctrl;
		static const int alt;
		static const int altgr;
		static const int lwin;
		static const int rwin;
		static const int menu;
		static const int scrolllock;
		static const int numlock;
		static const int capslock;

		/* This key's code. */
		const int code;

		bool is_a() const noexcept
		{ return code == a; }

		bool is_b() const noexcept
		{ return code == b; }

		bool is_c() const noexcept
		{ return code == c; }

		bool is_d() const noexcept
		{ return code == d; }

		bool is_e() const noexcept
		{ return code == e; }

		bool is_f() const noexcept
		{ return code == f; }

		bool is_g() const noexcept
		{ return code == g; }

		bool is_h() const noexcept
		{ return code == h; }

		bool is_i() const noexcept
		{ return code == i; }

		bool is_j() const noexcept
		{ return code == j; }

		bool is_k() const noexcept
		{ return code == k; }

		bool is_l() const noexcept
		{ return code == l; }

		bool is_m() const noexcept
		{ return code == m; }

		bool is_n() const noexcept
		{ return code == n; }

		bool is_o() const noexcept
		{ return code == o; }

		bool is_p() const noexcept
		{ return code == p; }

		bool is_q() const noexcept
		{ return code == q; }

		bool is_r() const noexcept
		{ return code == r; }

		bool is_s() const noexcept
		{ return code == s; }

		bool is_t() const noexcept
		{ return code == t; }

		bool is_u() const noexcept
		{ return code == u; }

		bool is_v() const noexcept
		{ return code == v; }

		bool is_w() const noexcept
		{ return code == w; }

		bool is_x() const noexcept
		{ return code == x; }

		bool is_y() const noexcept
		{ return code == y; }

		bool is_z() const noexcept
		{ return code == z; }

		bool is_0() const noexcept
		{ return code == num_0; }

		bool is_1() const noexcept
		{ return code == num_1; }

		bool is_2() const noexcept
		{ return code == num_2; }

		bool is_3() const noexcept
		{ return code == num_3; }

		bool is_4() const noexcept
		{ return code == num_4; }

		bool is_5() const noexcept
		{ return code == num_5; }

		bool is_6() const noexcept
		{ return code == num_6; }

		bool is_7() const noexcept
		{ return code == num_7; }

		bool is_8() const noexcept
		{ return code == num_8; }

		bool is_9() const noexcept
		{ return code == num_9; }

		bool is_pad_0() const noexcept
		{ return code == pad_0; }

		bool is_pad_1() const noexcept
		{ return code == pad_1; }

		bool is_pad_2() const noexcept
		{ return code == pad_2; }

		bool is_pad_3() const noexcept
		{ return code == pad_3; }

		bool is_pad_4() const noexcept
		{ return code == pad_4; }

		bool is_pad_5() const noexcept
		{ return code == pad_5; }

		bool is_pad_6() const noexcept
		{ return code == pad_6; }

		bool is_pad_7() const noexcept
		{ return code == pad_7; }

		bool is_pad_8() const noexcept
		{ return code == pad_8; }

		bool is_pad_9() const noexcept
		{ return code == pad_9; }

		bool is_f1() const noexcept
		{ return code == f1; }

		bool is_f2() const noexcept
		{ return code == f2; }

		bool is_f3() const noexcept
		{ return code == f3; }

		bool is_f4() const noexcept
		{ return code == f4; }

		bool is_f5() const noexcept
		{ return code == f5; }

		bool is_f6() const noexcept
		{ return code == f6; }

		bool is_f7() const noexcept
		{ return code == f7; }

		bool is_f8() const noexcept
		{ return code == f8; }

		bool is_f9() const noexcept
		{ return code == f9; }

		bool is_f10() const noexcept
		{ return code == f10; }

		bool is_f11() const noexcept
		{ return code == f11; }

		bool is_f12() const noexcept
		{ return code == f12; }

		bool is_escape() const noexcept
		{ return code == escape; }

		bool is_tilde() const noexcept
		{ return code == tilde; }

		bool is_minus() const noexcept
		{ return code == minus; }

		bool is_equals() const noexcept
		{ return code == equals; }

		bool is_backspace() const noexcept
		{ return code == backspace; }

		bool is_tab() const noexcept
		{ return code == tab; }

		bool is_openbrace() const noexcept
		{ return code == openbrace; }

		bool is_closebrace() const noexcept
		{ return code == closebrace; }

		bool is_enter() const noexcept
		{ return code == enter; }

		bool is_semicolon() const noexcept
		{ return code == semicolon; }

		bool is_quote() const noexcept
		{ return code == quote; }

		bool is_backslash() const noexcept
		{ return code == backslash; }

		bool is_backslash2() const noexcept
		{ return code == backslash2; }

		bool is_comma() const noexcept
		{ return code == comma; }

		bool is_fullstop() const noexcept
		{ return code == fullstop; }

		bool is_slash() const noexcept
		{ return code == slash; }

		bool is_space() const noexcept
		{ return code == space; }

		bool is_insert() const noexcept
		{ return code == insert; }

		bool is_delete() const noexcept
		{ return code == del; }

		bool is_home() const noexcept
		{ return code == home; }

		bool is_end() const noexcept
		{ return code == end; }

		bool is_pgup() const noexcept
		{ return code == pgup; }

		bool is_pgdn() const noexcept
		{ return code == pgdn; }

		bool is_left() const noexcept
		{ return code == left; }

		bool is_right() const noexcept
		{ return code == right; }

		bool is_up() const noexcept
		{ return code == up; }

		bool is_down() const noexcept
		{ return code == down; }

		bool is_pad_slash() const noexcept
		{ return code == pad_slash; }

		bool is_pad_asterisk() const noexcept
		{ return code == pad_asterisk; }

		bool is_pad_minus() const noexcept
		{ return code == pad_minus; }

		bool is_pad_plus() const noexcept
		{ return code == pad_plus; }

		bool is_pad_delete() const noexcept
		{ return code == pad_delete; }

		bool is_pad_enter() const noexcept
		{ return code == pad_enter; }

		bool is_printscreen() const noexcept
		{ return code == printscreen; }

		bool is_pause() const noexcept
		{ return code == pause; }

		bool is_abnt_c1() const noexcept
		{ return code == abnt_c1; }

		bool is_yen() const noexcept
		{ return code == yen; }

		bool is_kana() const noexcept
		{ return code == kana; }

		bool is_convert() const noexcept
		{ return code == convert; }

		bool is_noconvert() const noexcept
		{ return code == noconvert; }

		bool is_at() const noexcept
		{ return code == at; }

		bool is_circumflex() const noexcept
		{ return code == circumflex; }

		bool is_colon2() const noexcept
		{ return code == colon2; }

		bool is_kanji() const noexcept
		{ return code == kanji; }

		bool is_pad_equals() const noexcept
		{ return code == pad_equals; }

		bool is_backquote() const noexcept
		{ return code == backquote; }

		bool is_semicolon2() const noexcept
		{ return code == semicolon2; }

		bool is_command() const noexcept
		{ return code == command; }

		bool is_back() const noexcept
		{ return code == back; }

		bool is_volume_up() const noexcept
		{ return code == volume_up; }

		bool is_volume_down() const noexcept
		{ return code == volume_down; }

		bool is_search() const noexcept
		{ return code == search; }

		bool is_dpad_center() const noexcept
		{ return code == dpad_center; }

		bool is_button_x() const noexcept
		{ return code == button_x; }

		bool is_button_y() const noexcept
		{ return code == button_y; }

		bool is_dpad_up() const noexcept
		{ return code == dpad_up; }

		bool is_dpad_down() const noexcept
		{ return code == dpad_down; }

		bool is_dpad_left() const noexcept
		{ return code == dpad_left; }

		bool is_dpad_right() const noexcept
		{ return code == dpad_right; }

		bool is_select() const noexcept
		{ return code == select; }

		bool is_start() const noexcept
		{ return code == start; }

		bool is_button_l1() const noexcept
		{ return code == button_l1; }

		bool is_button_r1() const noexcept
		{ return code == button_r1; }

		bool is_button_l2() const noexcept
		{ return code == button_l2; }

		bool is_button_r2() const noexcept
		{ return code == button_r2; }

		bool is_button_a() const noexcept
		{ return code == button_a; }

		bool is_button_b() const noexcept
		{ return code == button_b; }

		bool is_thumbl() const noexcept
		{ return code == thumbl; }

		bool is_thumbr() const noexcept
		{ return code == thumbr; }

		bool is_unknown() const noexcept
		{ return code == unknown; }

		bool is_shift() const noexcept
		{ return code == lshift || code == rshift; }

		bool is_lshift() const noexcept
		{ return code == lshift; }

		bool is_rshift() const noexcept
		{ return code == rshift; }

		bool is_ctrl() const noexcept
		{ return code == lctrl || code == rctrl; }

		bool is_lctrl() const noexcept
		{ return code == lctrl; }

		bool is_rctrl() const noexcept
		{ return code == rctrl; }

		bool is_alt() const noexcept
		{ return code == alt; }

		bool is_altgr() const noexcept
		{ return code == altgr; }

		bool is_lwin() const noexcept
		{ return code == lwin; }

		bool is_rwin() const noexcept
		{ return code == rwin; }

		bool is_menu() const noexcept
		{ return code == menu; }

		bool is_scrolllock() const noexcept
		{ return code == scrolllock; }

		bool is_numlock() const noexcept
		{ return code == numlock; }

		bool is_capslock() const noexcept
		{ return code == capslock; }
	};
}
