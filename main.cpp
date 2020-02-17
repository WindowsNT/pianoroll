#include "stdafx.h"

HWND MainWindow = 0;
HINSTANCE hAppInstance = 0;
HICON hIcon1 = 0;

// ----
const TCHAR* ttitle = _T("Pianoroll App");
// ----



HMIDIOUT mIN = 0;
#include "pianoroll.hpp"
using namespace PR;

CComPtr<ID2D1HwndRenderTarget> d;
CComPtr<ID2D1Factory> fa;
PIANOROLL prx;

HANDLE hEv = CreateEvent(0, 0, 0, 0);
#include ".\\mt\\rw.hpp"
tlock<queue<DWORD>> q;
void PlayThread()
{
	for (;;)
	{
		WaitForSingleObject(hEv, INFINITE);
		DWORD e = 0;

		for (;;)
		{
			int slp = 50;
			q.writelock([&](queue<DWORD> & qq) {
				if (qq.empty())
					return;
				e = qq.front();
				qq.pop();
				if (qq.empty())
					slp = 250;
				});

			if (e == 0)
				break;
			midiOutShortMsg(mIN, e);
			if ((e & 0xF0) == 0xE0)
				continue;
			Sleep(slp);
			e &= 0x00FFFF;
			midiOutShortMsg(mIN, e);
		}
	}
}
void Play(int m, int vel,int micro)
{
	if (micro)
	{
		// 1000s after Midi note 0
		float fr = 16.35f * pow(2.0f, micro / 12000.0f);
		auto e = FrequencyToMidi(fr);
		q.writelock([&](queue<DWORD>& qq) {

			DWORD ps = 0x0000E0;
			ps |= std::get<1>(e) << 16;
			ps |= std::get<2>(e) << 8;
			qq.push(ps);

			DWORD ee = 0x000090;
			ee |= (vel << 16);
			ee |= std::get<0>(e) << 8;

			qq.push(ee);
			});
		SetEvent(hEv);
		return;
	}
	DWORD e = 0x000090;
	e |= (vel << 16);
	e |= m << 8;
	q.writelock([&](queue<DWORD> & qq) {
		qq.push(e);
		});
	SetEvent(hEv);
}

class M : public PIANOROLLCALLBACK
{
public:

	M()
	{
	}
	virtual HRESULT NoteAdded(PIANOROLL*, NOTE* n)
	{
		if (n->nonote > 0 || n->HasMetaEvent)
			return S_FALSE;
		Play(n->midi, n->vel,n->micro);
		return S_OK;
	}
	virtual HRESULT NoteRemoved(PIANOROLL*, NOTE*)
	{
		return S_OK;
	}
	virtual void RedrawRequest(PIANOROLL* p, unsigned long long param)
	{
		RECT rc;
		GetClientRect(MainWindow, &rc);
		d->BeginDraw();
		p->Paint(d, rc, param);
		d->EndDraw();
	}
	virtual HRESULT OnNoteChange(PIANOROLL*, NOTE* n1, NOTE* n2)
	{
		if (n1->midi != n2->midi || n1->vel != n2->vel || n1->micro != n2->micro)
		{
			if (n2->nonote > 0 || n2->HasMetaEvent)
				return S_FALSE;
			Play(n2->midi, n2->vel,n2->micro);
		}
		return S_OK;
	}
	virtual HRESULT OnNoteSelect(PIANOROLL*, NOTE* n, bool s)
	{
		if (!s)
			return S_OK;
		if (n->nonote > 0 || n->HasMetaEvent)
			return S_FALSE;
		Play(n->midi, n->vel,n->micro);
		return S_OK;
	}
	virtual void OnPianoOn(PIANOROLL*, int n,int vel,int ch)
	{
		DWORD e = 0x000090;
		e |= ch;
		e |= vel << 16;
		e |= n << 8;
		midiOutShortMsg(mIN, e);
	}
	virtual void OnPianoOff(PIANOROLL*, int off,int ch)
	{
		DWORD e = 0x000090;
		e |= ch;
		e |= off << 8;
		midiOutShortMsg(mIN, e);
	}

};



shared_ptr<M> c = make_shared<M>();

bool Playing = false;
void PlayX()
{
	vector<unsigned char> mmi;
	int BpM = 120;
	int TpB = 960;
	auto jmin = (1000 * 60) / BpM;
	unsigned long long AA = 0;
	prx.ToMidi(mmi, TpB, [&](PR::MIDI::MIDIITEM & it) -> HRESULT
		{

			if (!Playing)
				return E_FAIL;
			auto A = it.ti.abs;
			if (A != AA)
			{
				// Sleep before playing
				// in TpB Ticks -> (60/BpM)/1000 ms
				// In X   Ticks -  ?
				Sleep((DWORD)(jmin * (A - AA) / TpB));
			}

			if (it.ff == 0x51)
			{
				// Tempo
				BpM = it.GetTempo();
				jmin = (1000 * 60) / BpM;
			}
			if (it.event > 0)
			{
				if (PR::PIANOROLL::IsNoteOn(it.event))
				{
					prx.SelectNote(it.stridx, true);
				}
				if (PR::PIANOROLL::IsNoteOff(it.event))
				{
					prx.SelectNote(it.stridx, false);
				}

				midiOutShortMsg(mIN, it.event);
				wchar_t a[100];
				swprintf_s(a, 100, L"%06X\r\n", it.event);
				OutputDebugString(a);
			}
			AA = A;
			return S_OK;
		});

}

LRESULT CALLBACK Main_DP(HWND hh, UINT mm, WPARAM ww, LPARAM ll)
{
	switch (mm)
	{
	case WM_CREATE:
	{
		MainWindow = hh;
		prx.SetWindow(hh);
		prx.AddCallback(c);
		break;
	}

	case WM_COMMAND:
	{
		int LW = LOWORD(ww);
		UNREFERENCED_PARAMETER(LW);


		return 0;
	}

	case WM_CLOSE:
	{
		DestroyWindow(hh);
		return 0;
	}

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		if (ww == VK_SPACE)
		{
			if (Playing)
				Playing = false;
			else
			{
				Playing = true;
				std::thread pl(PlayX);
				pl.detach();
			}
			return 0;
		}
		if (ww == VK_F5)
		{
			// Save
			OPENFILENAME of = { 0 };
			of.lStructSize = sizeof(of);
			of.hwndOwner = hh;
			of.lpstrFilter = L"*.xml\0*.xml\0\0";
			vector<wchar_t> fnx(10000);
			of.lpstrFile = fnx.data();
			of.nMaxFile = 10000;
			of.lpstrDefExt = L"xml";
			of.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXPLORER;
			if (!GetSaveFileName(&of))
				return 0;

			DeleteFile(fnx.data());
			XML3::XML x(fnx.data());
			prx.Ser(x.GetRootElement());
			x.Save();

		}

		if (ww == VK_F6)
		{
			// Save MIDI

			OPENFILENAME of = { 0 };
			of.lStructSize = sizeof(of);
			of.hwndOwner = hh;
			of.lpstrFilter = L"*.mid\0*.mid\0\0";
			vector<wchar_t> fnx(10000);
			of.lpstrFile = fnx.data();
			of.nMaxFile = 10000;
			of.lpstrDefExt = L"mid";
			of.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXPLORER;
			if (!GetSaveFileName(&of))
				return 0;


			vector<unsigned char> mmf;
			prx.ToMidi(mmf);
			HANDLE hF = CreateFile(fnx.data(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
			if (hF != INVALID_HANDLE_VALUE)
			{
				DWORD A = 0;
				WriteFile(hF, mmf.data(),(DWORD) mmf.size(), &A, 0);
				CloseHandle(hF);
				ShellExecute(hh, L"open", fnx.data(), 0, 0, SW_SHOWNORMAL);
			}
			return 0;
		}

		if (ww == VK_F7)
		{
			// load 
			OPENFILENAME of = { 0 };
			of.lStructSize = sizeof(of);
			of.hwndOwner = hh;
			of.lpstrFilter = L"*.xml\0*.xml\0\0";
			vector<wchar_t> fnx(10000);
			of.lpstrFile = fnx.data();
			of.nMaxFile = 10000;
			of.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER;
			if (!GetOpenFileName(&of))
				return 0;

			XML3::XML x(fnx.data());
			prx.Unser(x.GetRootElement());

		}


		if (ww == VK_F8)
		{
			// load midi
			OPENFILENAME of = { 0 };
			of.lStructSize = sizeof(of);
			of.hwndOwner = hh;
			of.lpstrFilter = L"*.mid\0*.mid\0\0";
			vector<wchar_t> fnx(10000);
			of.lpstrFile = fnx.data();
			of.nMaxFile = 10000;
			of.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER;
			if (!GetOpenFileName(&of))
				return 0;
			vector<char> d2;
			HANDLE hF = CreateFile(fnx.data(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
			if (hF == INVALID_HANDLE_VALUE)
				return 0;
			LARGE_INTEGER li;
			GetFileSizeEx(hF, &li);
			// I guess no midi file is > 4gb
			d2.resize(li.LowPart);
			DWORD A = 0;
			ReadFile(hF, d2.data(), li.LowPart, &A, 0);
			CloseHandle(hF);
			prx.FromMidi((unsigned char*)d2.data(), d2.size());
		}


		if (ww == VK_F9)
		{
			// Save GMN

			OPENFILENAME of = { 0 };
			of.lStructSize = sizeof(of);
			of.hwndOwner = hh;
			of.lpstrFilter = L"*.gmn\0*.gmn\0\0";
			vector<wchar_t> fnx(10000);
			of.lpstrFile = fnx.data();
			of.nMaxFile = 10000;
			of.lpstrDefExt = L"gmn";
			of.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXPLORER;
			if (!GetSaveFileName(&of))
				return 0;


			string a = "% Pianoroll export - (C) Michael Chourdakis\r\n";
			a += prx.ToGuidoAll();
			HANDLE hF = CreateFile(fnx.data(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
			if (hF != INVALID_HANDLE_VALUE)
			{
				DWORD A = 0;
				WriteFile(hF, a.data(), (DWORD)a.size(), &A, 0);
				CloseHandle(hF);
				ShellExecute(hh, L"open", fnx.data(), 0, 0, SW_SHOWNORMAL);
			}
			return 0;
		}

		prx.KeyDown(ww, ll);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		prx.MouseMove(ww, ll);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		prx.LeftDown(ww, ll);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		prx.RightDown(ww, ll);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		prx.LeftUp(ww, ll);
		return 0;
	}
	case WM_LBUTTONDBLCLK:
	{
		prx.LeftDoubleClick(ww, ll);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hh, &ps);

		RECT rc;
		GetClientRect(hh, &rc);
		if (!fa)
			D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED, &fa);
		if (!d)
		{
			//				D2D1_RENDER_TARGET_PROPERTIES p;
			D2D1_HWND_RENDER_TARGET_PROPERTIES hp;
			hp.hwnd = hh;
			hp.pixelSize.width = rc.right;
			hp.pixelSize.height = rc.bottom;
			d.Release();

			fa->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hh, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &d);
		}
		d->BeginDraw();
		prx.Paint(d, rc);
		d->EndDraw();
		EndPaint(hh, &ps);
		return 0;
	}

	case WM_SIZE:
	{
		if (!d)
			return 0;

		RECT rc;
		GetClientRect(hh, &rc);
		D2D1_SIZE_U u;
		u.width = rc.right;
		u.height = rc.bottom;
		d->Resize(u);
		return 0;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hh, mm, ww, ll);
}



int __stdcall WinMain(HINSTANCE h, HINSTANCE, LPSTR, int)
{
	WSADATA wData;
	WSAStartup(MAKEWORD(2, 2), &wData);
	CoInitializeEx(0, COINIT_APARTMENTTHREADED);
	INITCOMMONCONTROLSEX icex = { 0 };
	icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_DATE_CLASSES | ICC_WIN95_CLASSES;
	icex.dwSize = sizeof(icex);
	InitCommonControlsEx(&icex);
	InitCommonControls();
	hIcon1 = LoadIcon(0, IDI_APPLICATION);
	midiOutOpen(&mIN, 0, 0, 0, 0);
	hAppInstance = h;
	std::thread tt(PlayThread);
	tt.detach();

	WNDCLASSEX wClass = { 0 };
	wClass.cbSize = sizeof(wClass);

	wClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
	wClass.lpfnWndProc = (WNDPROC)Main_DP;
	wClass.hInstance = h;
	wClass.hIcon = hIcon1;
	wClass.hCursor = 0;// LoadCursor(0, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wClass.lpszClassName = _T("CLASS");
	wClass.hIconSm = hIcon1;
	RegisterClassEx(&wClass);

	MainWindow = CreateWindowEx(0,
		_T("CLASS"),
		ttitle,
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		0, 0, h, 0);

	ShowWindow(MainWindow, SW_SHOW);


	MSG msg;

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ExitProcess(0);
	return 0;
}