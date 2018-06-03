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

		/* Set this key's code. */
		constexpr key(int code) noexcept: code{code}
		{}

		constexpr bool is_a() const
		{ return code == a; }

		constexpr bool is_b() const
		{ return code == b; }

		constexpr bool is_c() const
		{ return code == c; }

		constexpr bool is_d() const
		{ return code == d; }

		constexpr bool is_e() const
		{ return code == e; }

		constexpr bool is_f() const
		{ return code == f; }

		constexpr bool is_g() const
		{ return code == g; }

		constexpr bool is_h() const
		{ return code == h; }

		constexpr bool is_i() const
		{ return code == i; }

		constexpr bool is_j() const
		{ return code == j; }

		constexpr bool is_k() const
		{ return code == k; }

		constexpr bool is_l() const
		{ return code == l; }

		constexpr bool is_m() const
		{ return code == m; }

		constexpr bool is_n() const
		{ return code == n; }

		constexpr bool is_o() const
		{ return code == o; }

		constexpr bool is_p() const
		{ return code == p; }

		constexpr bool is_q() const
		{ return code == q; }

		constexpr bool is_r() const
		{ return code == r; }

		constexpr bool is_s() const
		{ return code == s; }

		constexpr bool is_t() const
		{ return code == t; }

		constexpr bool is_u() const
		{ return code == u; }

		constexpr bool is_v() const
		{ return code == v; }

		constexpr bool is_w() const
		{ return code == w; }

		constexpr bool is_x() const
		{ return code == x; }

		constexpr bool is_y() const
		{ return code == y; }

		constexpr bool is_z() const
		{ return code == z; }

		constexpr bool is_0() const
		{ return code == num_0; }

		constexpr bool is_1() const
		{ return code == num_1; }

		constexpr bool is_2() const
		{ return code == num_2; }

		constexpr bool is_3() const
		{ return code == num_3; }

		constexpr bool is_4() const
		{ return code == num_4; }

		constexpr bool is_5() const
		{ return code == num_5; }

		constexpr bool is_6() const
		{ return code == num_6; }

		constexpr bool is_7() const
		{ return code == num_7; }

		constexpr bool is_8() const
		{ return code == num_8; }

		constexpr bool is_9() const
		{ return code == num_9; }

		constexpr bool is_pad_0() const
		{ return code == pad_0; }

		constexpr bool is_pad_1() const
		{ return code == pad_1; }

		constexpr bool is_pad_2() const
		{ return code == pad_2; }

		constexpr bool is_pad_3() const
		{ return code == pad_3; }

		constexpr bool is_pad_4() const
		{ return code == pad_4; }

		constexpr bool is_pad_5() const
		{ return code == pad_5; }

		constexpr bool is_pad_6() const
		{ return code == pad_6; }

		constexpr bool is_pad_7() const
		{ return code == pad_7; }

		constexpr bool is_pad_8() const
		{ return code == pad_8; }

		constexpr bool is_pad_9() const
		{ return code == pad_9; }

		constexpr bool is_f1() const
		{ return code == f1; }

		constexpr bool is_f2() const
		{ return code == f2; }

		constexpr bool is_f3() const
		{ return code == f3; }

		constexpr bool is_f4() const
		{ return code == f4; }

		constexpr bool is_f5() const
		{ return code == f5; }

		constexpr bool is_f6() const
		{ return code == f6; }

		constexpr bool is_f7() const
		{ return code == f7; }

		constexpr bool is_f8() const
		{ return code == f8; }

		constexpr bool is_f9() const
		{ return code == f9; }

		constexpr bool is_f10() const
		{ return code == f10; }

		constexpr bool is_f11() const
		{ return code == f11; }

		constexpr bool is_f12() const
		{ return code == f12; }

		constexpr bool is_escape() const
		{ return code == escape; }

		constexpr bool is_tilde() const
		{ return code == tilde; }

		constexpr bool is_minus() const
		{ return code == minus; }

		constexpr bool is_equals() const
		{ return code == equals; }

		constexpr bool is_backspace() const
		{ return code == backspace; }

		constexpr bool is_tab() const
		{ return code == tab; }

		constexpr bool is_openbrace() const
		{ return code == openbrace; }

		constexpr bool is_closebrace() const
		{ return code == closebrace; }

		constexpr bool is_enter() const
		{ return code == enter; }

		constexpr bool is_semicolon() const
		{ return code == semicolon; }

		constexpr bool is_quote() const
		{ return code == quote; }

		constexpr bool is_backslash() const
		{ return code == backslash; }

		constexpr bool is_backslash2() const
		{ return code == backslash2; }

		constexpr bool is_comma() const
		{ return code == comma; }

		constexpr bool is_fullstop() const
		{ return code == fullstop; }

		constexpr bool is_slash() const
		{ return code == slash; }

		constexpr bool is_space() const
		{ return code == space; }

		constexpr bool is_insert() const
		{ return code == insert; }

		constexpr bool is_delete() const
		{ return code == del; }

		constexpr bool is_home() const
		{ return code == home; }

		constexpr bool is_end() const
		{ return code == end; }

		constexpr bool is_pgup() const
		{ return code == pgup; }

		constexpr bool is_pgdn() const
		{ return code == pgdn; }

		constexpr bool is_left() const
		{ return code == left; }

		constexpr bool is_right() const
		{ return code == right; }

		constexpr bool is_up() const
		{ return code == up; }

		constexpr bool is_down() const
		{ return code == down; }

		constexpr bool is_pad_slash() const
		{ return code == pad_slash; }

		constexpr bool is_pad_asterisk() const
		{ return code == pad_asterisk; }

		constexpr bool is_pad_minus() const
		{ return code == pad_minus; }

		constexpr bool is_pad_plus() const
		{ return code == pad_plus; }

		constexpr bool is_pad_delete() const
		{ return code == pad_delete; }

		constexpr bool is_pad_enter() const
		{ return code == pad_enter; }

		constexpr bool is_printscreen() const
		{ return code == printscreen; }

		constexpr bool is_pause() const
		{ return code == pause; }

		constexpr bool is_abnt_c1() const
		{ return code == abnt_c1; }

		constexpr bool is_yen() const
		{ return code == yen; }

		constexpr bool is_kana() const
		{ return code == kana; }

		constexpr bool is_convert() const
		{ return code == convert; }

		constexpr bool is_noconvert() const
		{ return code == noconvert; }

		constexpr bool is_at() const
		{ return code == at; }

		constexpr bool is_circumflex() const
		{ return code == circumflex; }

		constexpr bool is_colon2() const
		{ return code == colon2; }

		constexpr bool is_kanji() const
		{ return code == kanji; }

		constexpr bool is_pad_equals() const
		{ return code == pad_equals; }

		constexpr bool is_backquote() const
		{ return code == backquote; }

		constexpr bool is_semicolon2() const
		{ return code == semicolon2; }

		constexpr bool is_command() const
		{ return code == command; }

		constexpr bool is_back() const
		{ return code == back; }

		constexpr bool is_volume_up() const
		{ return code == volume_up; }

		constexpr bool is_volume_down() const
		{ return code == volume_down; }

		constexpr bool is_search() const
		{ return code == search; }

		constexpr bool is_dpad_center() const
		{ return code == dpad_center; }

		constexpr bool is_button_x() const
		{ return code == button_x; }

		constexpr bool is_button_y() const
		{ return code == button_y; }

		constexpr bool is_dpad_up() const
		{ return code == dpad_up; }

		constexpr bool is_dpad_down() const
		{ return code == dpad_down; }

		constexpr bool is_dpad_left() const
		{ return code == dpad_left; }

		constexpr bool is_dpad_right() const
		{ return code == dpad_right; }

		constexpr bool is_select() const
		{ return code == select; }

		constexpr bool is_start() const
		{ return code == start; }

		constexpr bool is_button_l1() const
		{ return code == button_l1; }

		constexpr bool is_button_r1() const
		{ return code == button_r1; }

		constexpr bool is_button_l2() const
		{ return code == button_l2; }

		constexpr bool is_button_r2() const
		{ return code == button_r2; }

		constexpr bool is_button_a() const
		{ return code == button_a; }

		constexpr bool is_button_b() const
		{ return code == button_b; }

		constexpr bool is_thumbl() const
		{ return code == thumbl; }

		constexpr bool is_thumbr() const
		{ return code == thumbr; }

		constexpr bool is_unknown() const
		{ return code == unknown; }

		constexpr bool is_shift() const
		{ return code == lshift || code == rshift; }

		constexpr bool is_lshift() const
		{ return code == lshift; }

		constexpr bool is_rshift() const
		{ return code == rshift; }

		constexpr bool is_ctrl() const
		{ return code == lctrl || code == rctrl; }

		constexpr bool is_lctrl() const
		{ return code == lctrl; }

		constexpr bool is_rctrl() const
		{ return code == rctrl; }

		constexpr bool is_alt() const
		{ return code == alt; }

		constexpr bool is_altgr() const
		{ return code == altgr; }

		constexpr bool is_lwin() const
		{ return code == lwin; }

		constexpr bool is_rwin() const
		{ return code == rwin; }

		constexpr bool is_menu() const
		{ return code == menu; }

		constexpr bool is_scrolllock() const
		{ return code == scrolllock; }

		constexpr bool is_numlock() const
		{ return code == numlock; }

		constexpr bool is_capslock() const
		{ return code == capslock; }
	};
}
