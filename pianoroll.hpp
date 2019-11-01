#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"Dwrite.lib")
#pragma comment(lib,"winmm.lib")
#include <atlbase.h>
#include ".\\xml\\xml3all.h"

// Todo
/*
	Split
	Transpose
	Legato/Staccato
*/

struct VISUALIZATIONPAINTINGPARAMETERS
{
	D2D1_COLOR_F bg = { 0,0,0,1 }, fg = { 1,1,1,1 }, sg = { 1,0,0,1 };
	unsigned long long P = 0;
};


namespace PR
{
	using namespace std;


	inline const wchar_t* gmpa[128] = {
		// 1- 16
		L"Acoustic Grand Piano",
		L"Bright Acoustic",
		L"Electric Grand",
		L"Honky-Tonk",
		L"Electric Piano 1",
		L"Electric Piano 2",
		L"Harpsichord",
		L"Clavinet",
		L"Celesta",
		L"Glockenspiel",
		L"Music Box",
		L"Vibraphone",
		L"Marimba",
		L"Xylophone",
		L"Tubular Bells",
		L"Dulcimer",

		//17-32
		L"Drawbar Organ",
		L"Percussive Organ",
		L"Rock Organ",
		L"Church Organ",
		L"Reed Organ",
		L"Accoridan",
		L"Harmonica",
		L"Tango Accordian",
		L"Nylon String Guitar",
		L"Steel String Guitar",
		L"Electric Jazz Guitar",
		L"Electric Clean Guitar",
		L"Electric Muted Guitar",
		L"Overdriven Guitar",
		L"Distortion Guitar",
		L"Guitar Harmonics",

		// 33-48
		L"Acoustic Bass",
		L"Electric Bass(finger)",
		L"Electric Bass(pick)",
		L"Fretless Bass",
		L"Slap Bass 1",
		L"Slap Bass 2",
		L"Synth Bass 1",
		L"Synth Bass 2",
		L"Violin",
		L"Viola",
		L"Cello",
		L"Contrabass",
		L"Tremolo Strings",
		L"Pizzicato Strings",
		L"Orchestral Strings",
		L"Timpani",

		// 49-64
		L"String Ensemble 1",
		L"String Ensemble 2",
		L"SynthStrings 1",
		L"SynthStrings 2",
		L"Choir Aahs",
		L"Voice Oohs",
		L"Synth Voice",
		L"Orchestra Hit",
		L"Trumpet",
		L"Trombone",
		L"Tuba",
		L"Muted Trumpet",
		L"French Horn",
		L"Brass Section",
		L"SynthBrass 1",
		L"SynthBrass 2",

		// 65-80
		L"Soprano Sax",
		L"Alto Sax",
		L"Tenor Sax",
		L"Baritone Sax",
		L"Oboe",
		L"English Horn",
		L"Bassoon",
		L"Clarinet",
		L"Piccolo",
		L"Flute",
		L"Recorder",
		L"Pan Flute",
		L"Blown Bottle",
		L"Skakuhachi",
		L"Whistle",
		L"Ocarina",

		// 81-96
		L"Lead 1 (square)",
		L"Lead 2 (sawtooth)",
		L"Lead 3 (calliope)",
		L"Lead 4 (chiff)",
		L"Lead 5 (charang)",
		L"Lead 6 (voice)",
		L"Lead 7 (fifths)",
		L"Lead 8 (bass+lead)",
		L"Pad 1 (new age)",
		L"Pad 2 (warm)",
		L"Pad 3 (polysynth)",
		L"Pad 4 (choir)",
		L"Pad 5 (bowed)",
		L"Pad 6 (metallic)",
		L"Pad 7 (halo)",
		L"Pad 8 (sweep)",


		// 97-112
		L"FX 1 (rain)",
		L"FX 2 (soundtrack)",
		L"FX 3 (crystal)",
		L"FX 4 (atmosphere)",
		L"FX 5 (brightness)",
		L"FX 6 (goblins)",
		L"FX 7 (echoes)",
		L"FX 8 (sci-fi)",
		L"Sitar",
		L"Banjo",
		L"Shamisen",
		L"Koto",
		L"Kalimba",
		L"Bagpipe",
		L"Fiddle",
		L"Shanai",


		// 113-128
		L"Tinkle Bell",
		L"Agogo",
		L"Steel Drums",
		L"Woodblock",
		L"Taiko Drum",
		L"Melodic Tom",
		L"Synth Drum",
		L"Reverse Cymbal",
		L"Guitar",
		L"Breath Noise",
		L"Seashore",
		L"Bird Tweet",
		L"Telephone Ring",
		L"Helicopter",
		L"Applause",
		L"Gunshot"
	};


	inline const wchar_t* gmdr[] = {

		// GM dr , 35-81
		L"Bass Drum 2"
		,L"Bass Drum 1"
		,L"Side Stick"
		,L"Snare Drum 1"
		,L"Hand Clap"
		,L"Snare Drum 2"
		,L"Low Tom 2"
		,L"Closed Hi-hat"
		,L"Low Tom 1"
		,L"Pedal Hi-hat"
		,L"Mid Tom 2"
		,L"Open Hi-hat"
		,L"Mid Tom 1"
		,L"High Tom 2"
		,L"Crash Cymbal 1"
		,L"High Tom 1"
		,L"Ride Cymbal 1"
		,L"Chinese Cymbal"
		,L"Ride Bell"
		,L"Tambourine"
		,L"Splash Cymbal"
		,L"Cowbell"
		,L"Crash Cymbal 2"
		,L"Vibra Slap"
		,L"Ride Cymbal 2"
		,L"High Bongo"
		,L"Low Bongo"
		,L"Mute High Conga"
		,L"Open High Conga"
		,L"Low Conga"
		,L"High Timbale"
		,L"Low Timbale"
		,L"High Agogo"
		,L"Low Agogo"
		,L"Cabasa"
		,L"Maracas"
		,L"Short Whistle"
		,L"Long Whistle"
		,L"Short Guiro"
		,L"Long Guiro"
		,L"Claves"
		,L"High Wood Block"
		,L"Low Wood Block"
		,L"Mute Cuica"
		,L"Open Cuica"
		,L"Mute Triangle"
		,L"Open Triangle"
	};


	class MIDI
	{
	public:

		struct MIDITIME
		{
			unsigned long long abs = 0;
			unsigned long delta = 0;
			unsigned long long smpl = 0;


			unsigned long long ToSamples(int TpB,int BpM,int SR)
			{
				if (abs == 0) return 0; //opti


				// Ticks per min
				int TpM = TpB * BpM;
				//int SRM = SR * 60;

				double dTpM = (double)TpM / 60.0;

				// In SRM samples, TpM ticks
				// ? samples, abs

				unsigned long long S = (unsigned long long)((double)(SR * abs) / (double)dTpM);
				return S;

			}

		};

		struct MIDIITEM
		{
			size_t stridx = 0;
			MIDITIME ti;
			DWORD event = 0;
			char ff = 0;
			vector<unsigned char> data; // For FF
			std::shared_ptr<void> anydata;
			bool operator <(const MIDIITEM& m2) const
			{
				if (ti.abs < m2.ti.abs)
					return true;
				return false;
			}

			void Marker(const wchar_t* txt)
			{
				ff = 0x6;
				data.resize(wcslen(txt) * 2);
				memcpy(data.data(), txt, wcslen(txt) * 2);
			}

			int GetTempo()
			{
/*												      (FirstDigit*0x10000) + (SecondDigit*0x100) + (ThirdDigit)
					Tempo =  60/(	---------------------------------------------------------    )
										           		1000000
*/

				if (ff != 0x51)
					return 0;
				if (data.size() != 3)
					return 0;
				double MSQ = 0;
				unsigned long long C = data[0];
				unsigned long long A = C;
				A *= 0x10000;
				MSQ += A;
				C = data[1];
				A = C;
				A *= 0x100;
				MSQ += A;
				C = data[2];
				A = C;
				MSQ += A;

				// MSQ = Microseconds per QN
				MSQ /= 1000.0;
				// MSQ = Milliseconds per QN
				MSQ /= 1000.0;
				// MSQ = Seconds per QN
				int Tempo = (int)(60 / MSQ);
				return Tempo;
			}

			void Tempo(int n)
			{
				// microseconds per quarter note
				event = 0;
				ff = 0x51;
				data.resize(3);

				// 120 bpm = 500000
				// n       = ?
				long long bu = (500000LL * 120) / n;
				data[0] = (bu >> 16) & 0xFF;
				data[1] = (bu >> 8) & 0xFF;
				data[2] = (bu) & 0xFF;
			}

			void Time(int n, int d, int bb = 8)
			{
				event = 0;
				ff = 0x58;
				data.resize(4);

				// Form, n/2^d
				data[0] = (char)n;
				data[1] = (char)pow(2, d);
				data[2] = 1;
				data[3] = (char)bb;
			}

			void Key(signed int sf, int mode)
			{
				event = 0;
				ff = 0x59;
				data.resize(2);
				data[0] = (char)sf;
				data[1] = (char)mode;
			}


			void End()
			{
				event = 0;
				ff = 0x2F;
				data.resize(0);
			}

		};

	private:

		void WriteVarLen(long value, vector<unsigned char>& b)
		{
			unsigned long long buffer = value & 0x7f;
			while ((value >>= 7) > 0)
			{
				buffer <<= 8;
				buffer |= 0x80;
				buffer += (value & 0x7f);
			}

			for (;;)
			{
				b.push_back((char)buffer);
				if (buffer & 0x80)
					buffer >>= 8;
				else
					break;
			}
		}

		unsigned long ReadVarLen(const unsigned char* inf, unsigned long& i)
		{
			unsigned long value = 0;
			unsigned char c = 0;

			unsigned char CC = inf[i++];
			value = (unsigned char)CC;
			if (value & 0x80)
			{
				value &= 0x7F;
				do
				{
					value = (value << 7) + ((c = inf[i++]) & 0x7F);
				} while (c & 0x80);
			}
			return(value);
		}


		void BigToLittle(unsigned short* t)
		{
			unsigned short f = *t;
			unsigned short nf = (f >> 8) | ((f & 0xFF) << 8);
			*t = nf;
		}

		void MIDI::BigToLittle(unsigned long* t)
		{
			unsigned long f = *t;
			unsigned char c0 = (unsigned char)(f >> 24);
			unsigned char c1 = (unsigned char)(f >> 16);
			unsigned char c2 = (unsigned char)(f >> 8);
			unsigned char c3 = (unsigned char)f;

			unsigned long nf = (c3 << 24) | (c2 << 16) | (c1 << 8) | c0;
			*t = nf;

		}


	public:

		HRESULT ReadMidi(const unsigned char* mididata, size_t midisize,int& tpb,map<int,vector<MIDIITEM>>& r)
		{
			if (!mididata || !midisize)
				return E_INVALIDARG;

			const  unsigned char* m = mididata;

			// Header
			if (memcmp(m, "MThd\0\0\0\x06", 8) != 0)
				return E_UNEXPECTED; // Not midi
			m += 8;

			// Number of Tracks
			int nTrk = 0;
			if (memcmp(m, "\0\0", 2) == 0) // single-midi
			{
				nTrk = 1;
			}
			else
			{
				// Possible multitrack
				char c1 = (m + 2)[0];
				char c2 = (m + 3)[0];
				nTrk = c1 * 16 + c2;
			}
			m += 4;

			// TicksPerBeat
			unsigned short TPB = 0;
			memcpy(&TPB, m, 2);
			m += 2;
			BigToLittle(&TPB);
			tpb = TPB;

			// 
		
			// Read tracks
			for (int ni = 0; ni < nTrk; ni++)
			{
				if (memcmp(m, "MTrk", 4) != 0)
					return E_UNEXPECTED; // Not midi
				m += 4;
				unsigned long TrackSize = 0;
				memcpy(&TrackSize, m, 4);
				m += 4;
				BigToLittle(&TrackSize);

				// Read the track
				const unsigned char* mm = m;

				unsigned long tsi = 0;
				unsigned char RunningStatus = 0;
				for (;;)
				{
					if (tsi >= TrackSize)
						break;
					unsigned long deltatime = ReadVarLen(mm, tsi);

					unsigned char ev = mm[tsi];
					if (ev < 0x80) // keep previous
					{
						ev = RunningStatus;
						tsi--;
					}

					RunningStatus = ev;

					if (ev >= 0x80 && ev <= 0xEF)
					{
						MIDIITEM it;
						it.ti.delta = deltatime;
						it.event = ev;
						unsigned int p1 = (unsigned char)mm[tsi + 1];
						it.event |= (p1 << 8);

						unsigned int p2 = (unsigned char)mm[tsi + 2];
						if (ev >= 0xC0 && ev <= 0xCF)
						{

						}
						else
						if (ev >= 0xD0 && ev <= 0xDF)
						{

						}
						else
							it.event |= (p2 << 16);
						r[ni].push_back(it);
					}

					if (ev >= 0x80 && ev <= 0x8F)
						tsi+= 3;
					else
					if (ev >= 0x90 && ev <= 0x9F)
						tsi+= 3;
					else
					if (ev >= 0xA0 && ev <= 0xAF)
						tsi+= 3;
					else
					if (ev >= 0xB0 && ev <= 0xBF)
						tsi+= 3;
					else
					if (ev >= 0xC0 && ev <= 0xCF)
						tsi+= 2;
					else
					if (ev >= 0xD0 && ev <= 0xDF)
						tsi+= 2;
					else
					if (ev >= 0xE0 && ev <= 0xEF)
						tsi+= 3;
					else
					if (ev == 0xF0)
					{
						tsi++;
						int evsize = mm[tsi];
						tsi += 1 + evsize;
					}
					else
					if (ev == 0xFF)
						{
						tsi++;
						unsigned char evcode = mm[tsi];
						tsi++;
						int evsize = mm[tsi];
						tsi++;
						MIDIITEM it;
						it.ti.delta = deltatime;
						it.ff = evcode;
						it.data.resize(evsize);
						memcpy(it.data.data(), mm + tsi, evsize);
						tsi += evsize;
						r[ni].push_back(it);
						}
					}
				m += TrackSize;
				}
			return S_OK;
		}


		void MetaInsert(MIDIITEM& e, vector<unsigned char>& d)
		{
			vector<unsigned char>& h1 = d;
			h1.resize(3);
			h1[0] = 0xFF;
			h1[1] = e.ff;
			h1[2] = (char)e.data.size();
			h1.insert(h1.end(), e.data.begin(), e.data.end());

		}

		void Write(int UseFormat, int TPB, vector<vector<MIDIITEM>>& TrackData, vector<unsigned char>& d)
		{
			// Header, tpb
			vector<char>hdr(11);
			if (UseFormat == 0)
				memcpy(hdr.data(), "\x4D\x54\x68\x64\x00\x00\x00\x06\x00\x00\x00", 11);
			if (UseFormat == 1)
				memcpy(hdr.data(), "\x4D\x54\x68\x64\x00\x00\x00\x06\x00\x01\x00", 11);
			if (UseFormat == 2)
				memcpy(hdr.data(), "\x4D\x54\x68\x64\x00\x00\x00\x06\x00\x02\x00", 11);

			auto nT = TrackData.size();
			d.insert(d.end(), hdr.begin(), hdr.end());
			d.push_back((char)nT); // Up to 256 tracks

			// TPB
			d.push_back((TPB >> 8) & 0xFF);
			d.push_back(TPB & 0xFF);


			// All tracks
			for (size_t t = 0; t < nT; t++)
			{
				auto& events = TrackData[t];
				bool HasOff = false;

				vector<char> td;

				// Header
				vector<char> thdr(4);
				memcpy(thdr.data(), "\x4D\x54\x72\x6B", 4);
				d.insert(d.end(), thdr.begin(), thdr.end());

				// data
				DWORD prevdt = 0;
				for (auto& it : events)
				{

					unsigned char XE = it.event & 0xFF;
					DWORD dt = 0;

					if (it.ti.abs)
					{
						dt = (DWORD)it.ti.abs - prevdt;
						prevdt += dt;
					}
					else
					{
						dt = it.ti.delta;
						prevdt += dt;
					}


					// dt, ev
					vector<unsigned char> h1;
					WriteVarLen(dt, h1);
					td.insert(td.end(), h1.begin(), h1.end());

					if ((XE >= 0x90 && XE <= 0x9F) || (XE >= 0x80 && XE <= 0x8F) || (XE >= 0xA0 && XE <= 0xAF) || (XE >= 0xB0 && XE <= 0xBF) || (XE >= 0xE0 && XE <= 0xEF))
					{
						h1.resize(3);
						memcpy(h1.data(), &it.event, 3);
					}
					else
						if ((XE >= 0xC0 && XE <= 0xCF) || (XE >= 0xD0 && XE <= 0xDF))
						{
							h1.resize(2);
							memcpy(h1.data(), &it.event, 2);
						}
						else
						{
							// 0xFX
							// Code, length, data
							MetaInsert(it, h1);
							if (it.ff == 0x2F)
								HasOff = true;
						}

					td.insert(td.end(), h1.begin(), h1.end());


				}

				// Footer
				MIDIITEM it;
				it.End();

				if (!HasOff)
				{
					thdr.resize(4);
					memcpy(thdr.data(), "\x0\xFF\x2F\x00", 4);
					td.insert(td.end(), thdr.begin(), thdr.end());
				}

				// Write it
				unsigned long MidiDataBytes = (unsigned long)td.size();
				d.push_back((MidiDataBytes >> 24));
				d.push_back((MidiDataBytes >> 16) & 0xFF);
				d.push_back((MidiDataBytes >> 8) & 0xFF);
				d.push_back((MidiDataBytes) & 0xFF);
				d.insert(d.end(), td.begin(), td.end());

			}


		}

	};



	class PIANOROLL;
	class NOTE;
#ifdef _WIN64
	typedef long long ssize_t;
#else
	typedef long ssize_t;
#endif

	static void MidiNoteName(wchar_t* s, int mid, int key, int mode)
	{
		if (!s)
			return;

		mid %= 12;

		if (mid == 0) 
		{
			wcscpy_s(s, 10, L"C");
			if (key >= 7 || (key == 4 && mode == 1))
				wcscpy_s(s, 10, L"B\u266F");
		}
		if (mid == 1)
		{
			if (key >= 0)
				wcscpy_s(s, 10, L"C\u266F");
			else
				wcscpy_s(s, 10, L"D\u266D");
		}

		if (mid == 2) wcscpy_s(s, 10, L"D");

		if (mid == 3)
		{
			if (key >= 0)
				wcscpy_s(s, 10, L"D\u266F");
			else
				wcscpy_s(s, 10, L"E\u266D");
		}

		if (mid == 4)
		{
			wcscpy_s(s, 10, L"E");
			if (key <= -7)
				wcscpy_s(s, 10, L"F\u266D");
		}


		if (mid == 5)
		{
			wcscpy_s(s, 10, L"F");
			if (key >= 6 || (key == 3 && mode == 1))
				wcscpy_s(s, 10, L"E\u266F");
		}

		if (mid == 6)
		{
			if (key >= 0)
				wcscpy_s(s, 10, L"F\u266F");
			else
				wcscpy_s(s, 10, L"G\u266D");
		}

		if (mid == 7) wcscpy_s(s, 10, L"G");

		if (mid == 8)
		{
			if (key >= 0)
				wcscpy_s(s, 10, L"G\u266F");
			else
				wcscpy_s(s, 10, L"A\u266D");
		}

		if (mid == 9) wcscpy_s(s, 10, L"A");

		if (mid == 10)
		{
			if (key >= 0)
				wcscpy_s(s, 10, L"A\u266F");
			else
				wcscpy_s(s, 10, L"B\u266D");
		}

		if (mid == 11)
		{
			wcscpy_s(s, 10, L"B");
			if (key <= -6)
				wcscpy_s(s, 10, L"C\u266D");
		}

		return;
	}

	class PIANOROLLCALLBACK
	{
	public:

		virtual HRESULT NoteAdded(PIANOROLL* pr, NOTE*) = 0;
		virtual HRESULT NoteRemoved(PIANOROLL* pr, NOTE*) = 0;
		virtual void RedrawRequest(PIANOROLL* pr, unsigned long long param) = 0;
		virtual HRESULT OnNoteChange(PIANOROLL* pr, NOTE* oldn, NOTE* newn) = 0;
		virtual HRESULT OnNoteSelect(PIANOROLL* pr, NOTE* oldn, bool) = 0;
		virtual void OnPianoOn(PIANOROLL*, int n,int vel,int ch) = 0;
		virtual void OnPianoOff(PIANOROLL*, int off,int ch) = 0;
	};


	class FRACTION
	{
	public:
		mutable ssize_t n = 0;
		mutable ssize_t d = 1;

		void Ser(XML3::XMLElement& e) const
		{
			e.vv("n").SetValueInt((int)n);
			e.vv("d").SetValueInt((int)d);
		}
		void Unser(XML3::XMLElement& e)
		{
			n = e.vv("n").GetValueInt();
			d = e.vv("d").GetValueInt();
		}


		static void Om(const FRACTION& f1, const FRACTION& f2)
		{
			if (f1.d == f2.d)
				return;
/*			if (f1.d <= 0 || f2.d <= 0)
			{
				f1.d = -10;
			}
*/
			f1.simplify();
			f2.simplify();
			auto f1d = f1.d;
			f1.bmul(f2.d);
			f2.bmul(f1d);

			if (f1.d < 0 && f2.d < 0)
			{
				f1.d = -f1.d;
				f2.d = -f2.d;
				f1.n = -f1.n;
				f2.n = -f1.n;
			}


			return;
		}


		static ssize_t gcd(ssize_t num1, ssize_t num2)
		{
			if (num1 == 0 || num2 == 0)
				return 0;
			ssize_t remainder = num2 % num1;
			if (remainder != 0)
				return gcd(remainder, num1);
			return num1;
		}



		const FRACTION & simplify() const
		{
			if (n == 0)
			{
				d = 1;
				return *this;
			}
			ssize_t g = gcd(n, d);
			if (g == 0)
				return *this;
			n /= g;
			d /= g;
			return *this;
		}


		float r()
		{
			if (!d)
				return 0; // whops
			return (float)n / (float)d;
		}

		void Set(ssize_t nu = 0, ssize_t de = 1)
		{
			n = nu;
			d = de;
			if (d == 0)
				d = 1;
		}

		FRACTION(ssize_t nu = 0, ssize_t de = 1)
		{
			Set(nu, de);
		}

		const FRACTION& bmul(ssize_t de) const
		{
			n *= de;
			d *= de;
			return *this;
		}

		FRACTION& operator +=(const FRACTION & a)
		{
			FRACTION::Om(*this, a);
			n += a.n;
			return *this;
		}
		FRACTION& operator -=(const FRACTION & a)
		{
			FRACTION::Om(*this, a);
			n -= a.n;
			return *this;
		}

		bool operator ==(const FRACTION & f)  const
		{
			Om(*this, f);
			if (n == f.n)
				return true;
			return false;
		}
		bool operator !=(const FRACTION & f)  const
		{
			return !operator==(f);
		}

		bool operator <(FRACTION & f)  const
		{
			Om(*this, f); // Ensures also positive denomiator
			if (n < f.n)
				return true;
			return false;
		}
		bool operator <=(FRACTION & f)  const
		{
			Om(*this, f);
			if (n <= f.n)
				return true;
			return false;
		}
		bool operator >(FRACTION & f)  const
		{
			Om(*this, f);
			if (n > f.n)
				return true;
			return false;
		}
		bool operator >=(FRACTION & f)  const
		{
			Om(*this, f);
			if (n >= f.n)
				return true;
			return false;
		}
	};

	inline FRACTION operator +(const FRACTION & a, const FRACTION & b)
	{
		FRACTION::Om(a, b);
		FRACTION f(a.n + b.n, a.d);
		return f;
	}
	inline FRACTION operator -(const FRACTION & a, const FRACTION & b)
	{
		FRACTION::Om(a, b);
		FRACTION f(a.n - b.n, a.d);
		return f;
	}
	inline FRACTION operator /(const FRACTION & a, const FRACTION & b)
	{
		FRACTION f(a.n * b.d, a.d * b.n);
		return f.simplify();
	}
	inline bool operator <(const FRACTION & a, const FRACTION & b)
	{
		FRACTION::Om(a, b);
		if (a.n < b.n)
			return true;
		return false;
	}
	inline bool operator >(const FRACTION & a, const FRACTION & b)
	{
		FRACTION::Om(a, b);
		if (a.n > b.n)
			return true;
		return false;
	}
	inline bool operator <=(const FRACTION& a, const FRACTION& b)
	{
		return !operator>(a,b);
	}
	inline bool operator >=(const FRACTION& a, const FRACTION& b)
	{
		return !operator<(a, b);
	}


	class ABSPOSITION
	{
	public:
		size_t beats;
		FRACTION f;

		size_t ToTpb(int TPB)
		{
			size_t y = TPB * beats;
			y += (TPB * f.n * 4) / f.d;
			return y;
		}

		bool operator !=(const ABSPOSITION& b)
		{
			return !operator==(b);
		}

		bool operator ==(const ABSPOSITION& b)
		{
			if (beats == b.beats && f == b.f)
				return true;
				return false;
		}

		bool operator <(const ABSPOSITION& b)
		{
			if (beats < b.beats)
				return true;
			if (beats == b.beats && f < b.f)
				return true;
			return false;
		}
		bool operator >(const ABSPOSITION& b)
		{
			if (beats > b.beats)
				return true;
			if (beats == b.beats && f > b.f)
				return true;
			return false;
		}

		bool operator <=(const ABSPOSITION& b)
		{
			if (beats < b.beats)
				return true;
			if (beats == b.beats && f <= b.f)
				return true;
			return false;
		}
		bool operator >=(const ABSPOSITION& b)
		{
			if (beats > b.beats)
				return true;
			if (beats == b.beats && f >= b.f)
				return true;
			return false;
		}
	};


	class POSITION
	{
	public:
		size_t m = 0;
		FRACTION f;
		int noteht = 0;

		void Ser(XML3::XMLElement& e) const
		{
			e.vv("m").SetValueULongLong(m);
			f.Ser(e);
		}
		void Unser(XML3::XMLElement& e)
		{
			m = (size_t)e.vv("m").GetValueULongLong();
			f.Unser(e);
		}

		bool operator <(const POSITION& p) const
		{
			if (m < p.m)
				return true;
			if (m > p.m)
				return false;
			if (f < p.f)
				return true;
			return false;
		}

		bool operator ==(const POSITION& p)  const
		{
			if (m != p.m)
				return false;
			if (f != p.f)
				return false;
			return true;
		}

		bool operator !=(const POSITION & p)  const
		{
			return !operator ==(p);
		}
		bool operator >(const POSITION & p)  const
		{
			if (m > p.m)
				return true;
			if (m < p.m)
				return false;
			if (f > p.f)
				return true;
			return false;
		}
		bool operator >=(const POSITION& p)  const
		{
			return !operator <(p);
		}
		bool operator <=(const POSITION& p)  const
		{
			return !operator >(p);
		}

	};

	class MARKER
	{
	public:

		POSITION p;
		wstring t;


		void Ser(XML3::XMLElement& e) const
		{
			e.vv("t").SetValue(XML3::XMLU(t.c_str()));
			p.Ser(e["p"]);
		}
		void Unser(XML3::XMLElement& e)
		{
			p.Unser(e["p"]);
			t = e.vv("t").GetWideValue();
		}



		float VisiblePos = -1;

		bool operator ==(const MARKER& kk) const
		{
			if (p == kk.p)
				return true;
			return false;
		}
		bool operator<(const MARKER & kk)
		{
			if (p < kk.p)
				return true;
			return false;
		}

	};

	class PART
	{
	public:
		D2D1_RECT_F full;
		wstring n;
		bool S = false;

		void Ser(size_t idx,XML3::XMLElement& el) const
		{
			el.vv("n").SetValue(XML3::XMLU(n.c_str()));
			el.vv("i").SetValueULongLong(idx);
		}

		unsigned long long Unser(XML3::XMLElement& e)
		{
			n = e.vv("n").GetWideValue();
			return e.vv("i").GetValueULongLong();
		}
	};

	class NOTE
	{
	public:

		int midi = 0;
		int Selected = 0;
		POSITION p;
		FRACTION d;
		int vel = 127;
		int ch = 0;
		int layer = 0;
		size_t part = 0;
		std::shared_ptr<void> any;

		// And a non note event
		DWORD nonote = 0;

		// And FF events (specific like tempo etc and Sysex)
		bool HasMetaEvent = 0;
		unsigned char MetaEvent = 0;
		vector<unsigned char> MetaEventData;

		D2D1_RECT_F dr;

		void Ser(XML3::XMLElement& e) const
		{
			e.vv("e").SetValueUInt(nonote);
			e.vv("l").SetValueInt(layer);
			e.vv("c").SetValueInt(ch);
			e.vv("v").SetValueInt(vel);
			e.vv("m").SetValueInt(midi);
			e.vv("p").SetValueULongLong(part);

			if (HasMetaEvent)
			{
				e.vv("f1").SetValueUInt(HasMetaEvent);
				e.vv("f2").SetValueUInt(MetaEvent);
				e.vv("f3").SetBinaryValue((const char*)MetaEventData.data(), MetaEventData.size());
			}

			p.Ser(e["pos"]);
			d.Ser(e["dur"]);
		}
		void Unser(XML3::XMLElement& e) 
		{
			layer = e.vv("l").GetValueInt();
			ch = e.vv("c").GetValueInt();
			vel = e.vv("v").GetValueInt();
			midi = e.vv("m").GetValueInt();
			nonote = e.vv("e").GetValueUInt();
			part = e.vv("p").GetValueULongLong(0);

			HasMetaEvent = e.vv("f1").GetValueUInt(0);
			if (HasMetaEvent)
			{
				MetaEvent = (unsigned char)e.vv("f2").GetValueUInt(0);
				auto b = e.vv("f3").GetBinaryValue();
				MetaEventData.resize(b.size());
				memcpy(MetaEventData.data(), b.p(), b.size());
			}

			p.Unser(e["pos"]);
			d.Unser(e["dur"]);
		}

		POSITION EndX() const
		{
			POSITION pp = p;
			pp.f += d;
			return pp;
		}


		bool operator <(const NOTE& n2)
		{
			if (p < n2.p)
				return true;
			if (p > n2.p)
				return false;
			if (midi < n2.midi)
				return true;
			return false;
		}

		bool PartSelected(map<size_t, PART>& parts)
		{
			if (parts[part].S)
				return true;
			return false;
		}
	};


	class MIDIINHANDLE
	{
	public:

		int mid = 0;
		HMIDIIN m = 0;

		MIDIINHANDLE()
		{
			m = 0;
			mid = 0;
		}

		MIDIINHANDLE& operator=(const MIDIINHANDLE& h)
		{
			Close();
			midiInOpen(&m, h.mid, 0, 0, 0);
			mid = h.mid;
			return *this;
		}

		MIDIINHANDLE(const MIDIINHANDLE& h)
		{
			operator=(h);
		}

		void Close()
		{
			if (m)
			{
				midiInStop(m);
				midiInClose(m);
			}
			m = 0;

		}
		~MIDIINHANDLE()
		{
			Close();
		}
	};

	class PIANOROLL
	{
	private:


		static void CALLBACK MidiInProc(
			HMIDIIN,
			UINT msg,
			DWORD_PTR dwInstance,
			DWORD_PTR e,
			DWORD_PTR
		)
		{
			PIANOROLL* pr = (PIANOROLL*)dwInstance;
			if (!pr)
				return;

			if (msg != MM_MIM_DATA)
				return;

			if ((e & 0xF0) == 0x90)
			{
				// Note
				pr->InsertNoteFromMidiIn((DWORD)e);
			}
			if ((e & 0xF0) == 0x80)
			{
				// Note
				pr->InsertNoteFromMidiIn((DWORD)e);
			}

		}

		struct ASKTEXT
		{
			const wchar_t* ti;
			const wchar_t* as;
			wchar_t* re;
			int P;
			wstring* re2;
			int mx = 1000;
		};

		static INT_PTR CALLBACK A_DP(HWND hh, UINT mm, WPARAM ww, LPARAM ll)
		{
			static ASKTEXT* as = 0;
			switch (mm)
			{
			case WM_INITDIALOG:
			{
				as = (ASKTEXT*)ll;
				SetWindowText(hh, as->ti);
				if (as->P != 2)
				{
					SetWindowText(GetDlgItem(hh, 101), as->as);
					if (as->re)
						SetWindowText(GetDlgItem(hh, 102), as->re);
					if (as->re2)
						SetWindowText(GetDlgItem(hh, 102), as->re2->c_str());
				}
				else
					SetWindowText(GetDlgItem(hh, 701), as->as);
				if (as->P == 1)
				{
					auto w = GetWindowLongPtr(GetDlgItem(hh, 102), GWL_STYLE);
					w |= ES_PASSWORD;
					SetWindowLongPtr(GetDlgItem(hh, 102), GWL_STYLE, w);
				}
				return true;
			}
			case WM_COMMAND:
			{
				if (LOWORD(ww) == IDOK)
				{
					wchar_t re1[1000] = { 0 };
					wchar_t re2[1000] = { 0 };
					//					MessageBox(0, L"foo", 0, 0);
					if (as->P == 2)
					{
						GetWindowText(GetDlgItem(hh, 101), re1, 1000);
						GetWindowText(GetDlgItem(hh, 102), re2, 1000);
						if (wcscmp(re1, re2) != 0 || wcslen(re1) == 0)
						{
							SetWindowText(GetDlgItem(hh, 101), L"");
							SetWindowText(GetDlgItem(hh, 102), L"");
							SetFocus(GetDlgItem(hh, 101));
							return 0;
						}
						wcscpy_s(as->re, 1000, re1);
						EndDialog(hh, IDOK);
						return 0;
					}

					if (as->re2)
					{
						int lex = GetWindowTextLength(GetDlgItem(hh, 102));
						vector<wchar_t> re(lex + 100);
						GetWindowText(GetDlgItem(hh, 102), re.data(), lex + 100);
						*as->re2 = re.data();
						EndDialog(hh, IDOK);
					}
					else
					{
						GetWindowText(GetDlgItem(hh, 102), as->re, as->mx);
						EndDialog(hh, IDOK);
					}
					return 0;
				}
				if (LOWORD(ww) == IDCANCEL)
				{
					EndDialog(hh, IDCANCEL);
					return 0;
				}
			}
			}
			return 0;
		}

		inline bool AskText(HWND hh, const TCHAR * ti, const TCHAR * as, TCHAR * re, wstring * re2 = 0, int mxt = 1000)
		{
			const char* res = "\xC4\x0A\xCA\x90\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\x6D\x01\x3E\x00\x00\x00\x00\x00\x00\x00\x0A\x00\x54\x00\x61\x00\x68\x00\x6F\x00\x6D\x00\x61\x00\x00\x00\x01\x00\x00\x50\x00\x00\x00\x00\x0A\x00\x09\x00\x1C\x01\x1A\x00\x65\x00\xFF\xFF\x82\x00\x00\x00\x00\x00\x00\x00\x80\x00\x81\x50\x00\x00\x00\x00\x0A\x00\x29\x00\x1D\x01\x0F\x00\x66\x00\xFF\xFF\x81\x00\x00\x00\x00\x00\x00\x00\x00\x03\x01\x50\x00\x00\x00\x00\x2F\x01\x16\x00\x32\x00\x0E\x00\x01\x00\xFF\xFF\x80\x00\x4F\x00\x4B\x00\x00\x00\x00\x00\x00\x00\x00\x03\x01\x50\x00\x00\x00\x00\x2F\x01\x29\x00\x32\x00\x0E\x00\x02\x00\xFF\xFF\x80\x00\x43\x00\x61\x00\x6E\x00\x63\x00\x65\x00\x6C\x00\x00\x00\x00\x00";
			ASKTEXT a = { ti,as,re,0,re2,mxt };
			return (DialogBoxIndirectParam(GetModuleHandle(0), (LPCDLGTEMPLATEW)res, hh, A_DP, (LPARAM)& a) == IDOK);
		}

		inline static INT_PTR CALLBACK SS_DP(HWND hh, UINT mm, WPARAM , LPARAM )
		{
			switch (mm)
			{
				case WM_CLOSE:
				{
					EndDialog(hh, 0);
					return 0;
				}
				case WM_INITDIALOG:
				{
					SetFocus(GetDlgItem(hh, 101));
					return 0;
				}
			}
			return 0;
		}

		inline bool SpecialSelectionDP(HWND hh)
		{
			const char* res = "\xCC\x08\xC8\x90\x00\x00\x00\x00\x19\x00\x00\x00\x00\x00\x3B\x01\xD9\x00\x00\x00\x00\x00\x53\x00\x65\x00\x6C\x00\x65\x00\x63\x00\x74\x00\x69\x00\x6F\x00\x6E\x00\x00\x00\x08\x00\x4D\x00\x73\x00\x20\x00\x53\x00\x68\x00\x65\x00\x6C\x00\x6C\x00\x20\x00\x44\x00\x6C\x00\x67\x00\x00\x00\x00\x00\x07\x00\x00\x50\x00\x00\x00\x00\x08\x00\x09\x00\x2E\x01\xB5\x00\xFF\xFF\xFF\xFF\x80\x00\x53\x00\x65\x00\x6C\x00\x65\x00\x63\x00\x74\x00\x69\x00\x6F\x00\x6E\x00\x20\x00\x4F\x00\x70\x00\x74\x00\x69\x00\x6F\x00\x6E\x00\x73\x00\x00\x00\x00\x00\x00\x00\x00\x50\x00\x00\x00\x00\x12\x00\x1A\x00\x36\x00\x0A\x00\xFF\xFF\xFF\xFF\x82\x00\x50\x00\x6F\x00\x73\x00\x69\x00\x74\x00\x69\x00\x6F\x00\x6E\x00\x20\x00\x46\x00\x72\x00\x6F\x00\x6D\x00\x3A\x00\x00\x00\x00\x00\x00\x00\x80\x00\x81\x50\x00\x00\x00\x00\x53\x00\x15\x00\x6B\x00\x0F\x00\x65\x00\xFF\xFF\x81\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x50\x00\x00\x00\x00\x12\x00\x2C\x00\x36\x00\x0A\x00\xFF\xFF\xFF\xFF\x82\x00\x50\x00\x6F\x00\x73\x00\x69\x00\x74\x00\x69\x00\x6F\x00\x6E\x00\x20\x00\x54\x00\x6F\x00\x3A\x00\x00\x00\x00\x00\x00\x00\x80\x00\x81\x50\x00\x00\x00\x00\x53\x00\x28\x00\x6B\x00\x0F\x00\x66\x00\xFF\xFF\x81\x00\x00\x00\x00\x00\x00\x00\x03\x00\x01\x50\x00\x00\x00\x00\x11\x00\x50\x00\x37\x00\x08\x00\xD3\x00\xFF\xFF\x80\x00\x43\x00\x68\x00\x61\x00\x6E\x00\x6E\x00\x65\x00\x6C\x00\x20\x00\x66\x00\x72\x00\x6F\x00\x6D\x00\x00\x00\x00\x00\x00\x00\x03\x02\x20\x50\x00\x00\x00\x00\x53\x00\x4E\x00\x4E\x00\x1E\x00\xD4\x00\xFF\xFF\x85\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x50\x00\x00\x00\x00\xAC\x00\x50\x00\x10\x00\x08\x00\xFF\xFF\xFF\xFF\x82\x00\x74\x00\x6F\x00\x00\x00\x00\x00\x00\x00\x03\x02\x20\x50\x00\x00\x00\x00\xC3\x00\x4E\x00\x4E\x00\x1E\x00\xD5\x00\xFF\xFF\x85\x00\x00\x00\x00\x00\x00\x00\x03\x00\x01\x50\x00\x00\x00\x00\x11\x00\x62\x00\x37\x00\x08\x00\xDD\x00\xFF\xFF\x80\x00\x56\x00\x65\x00\x6C\x00\x6F\x00\x63\x00\x69\x00\x74\x00\x79\x00\x20\x00\x66\x00\x72\x00\x6F\x00\x6D\x00\x00\x00\x00\x00\x03\x02\x20\x50\x00\x00\x00\x00\x53\x00\x5F\x00\x4E\x00\x1E\x00\xDE\x00\xFF\xFF\x85\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x50\x00\x00\x00\x00\xAC\x00\x61\x00\x10\x00\x08\x00\xFF\xFF\xFF\xFF\x82\x00\x74\x00\x6F\x00\x00\x00\x00\x00\x00\x00\x03\x02\x20\x50\x00\x00\x00\x00\xC3\x00\x5F\x00\x4E\x00\x1E\x00\xDF\x00\xFF\xFF\x85\x00\x00\x00\x00\x00\x00\x00\x03\x00\x01\x50\x00\x00\x00\x00\x11\x00\x72\x00\x37\x00\x08\x00\xE7\x00\xFF\xFF\x80\x00\x4C\x00\x61\x00\x79\x00\x65\x00\x72\x00\x20\x00\x66\x00\x72\x00\x6F\x00\x6D\x00\x00\x00\x00\x00\x00\x00\x03\x02\x20\x50\x00\x00\x00\x00\x53\x00\x70\x00\x4E\x00\x1E\x00\xE8\x00\xFF\xFF\x85\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x50\x00\x00\x00\x00\xAC\x00\x71\x00\x10\x00\x08\x00\xFF\xFF\xFF\xFF\x82\x00\x74\x00\x6F\x00\x00\x00\x00\x00\x00\x00\x03\x02\x20\x50\x00\x00\x00\x00\xC3\x00\x70\x00\x4E\x00\x1E\x00\xE9\x00\xFF\xFF\x85\x00\x00\x00\x00\x00\x00\x00\x03\x00\x01\x50\x00\x00\x00\x00\x11\x00\x83\x00\x37\x00\x08\x00\xF1\x00\xFF\xFF\x80\x00\x4E\x00\x6F\x00\x74\x00\x65\x00\x20\x00\x66\x00\x72\x00\x6F\x00\x6D\x00\x00\x00\x00\x00\x03\x02\x20\x50\x00\x00\x00\x00\x53\x00\x81\x00\x4E\x00\x1E\x00\xF2\x00\xFF\xFF\x85\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x50\x00\x00\x00\x00\xAC\x00\x83\x00\x10\x00\x08\x00\xFF\xFF\xFF\xFF\x82\x00\x74\x00\x6F\x00\x00\x00\x00\x00\x00\x00\x03\x02\x20\x50\x00\x00\x00\x00\xC3\x00\x81\x00\x4E\x00\x1E\x00\xF3\x00\xFF\xFF\x85\x00\x00\x00\x00\x00\x00\x00\x03\x00\x01\x50\x00\x00\x00\x00\x09\x00\xC5\x00\x4D\x00\x0E\x00\xDF\x03\xFF\xFF\x80\x00\x41\x00\x70\x00\x70\x00\x65\x00\x6E\x00\x64\x00\x20\x00\x74\x00\x6F\x00\x20\x00\x65\x00\x78\x00\x69\x00\x73\x00\x74\x00\x69\x00\x6E\x00\x67\x00\x00\x00\x00\x00\x00\x00\x03\x00\x01\x50\x00\x00\x00\x00\x5F\x00\xC5\x00\x2E\x00\x0E\x00\xE0\x03\xFF\xFF\x80\x00\x52\x00\x65\x00\x76\x00\x65\x00\x72\x00\x73\x00\x65\x00\x00\x00\x00\x00\x01\x00\x01\x50\x00\x00\x00\x00\xCA\x00\xC3\x00\x32\x00\x0E\x00\x01\x00\xFF\xFF\x80\x00\x4F\x00\x4B\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x50\x00\x00\x00\x00\x01\x01\xC3\x00\x32\x00\x0E\x00\x02\x00\xFF\xFF\x80\x00\x43\x00\x61\x00\x6E\x00\x63\x00\x65\x00\x6C\x00\x00\x00\x00\x00";
			DialogBoxIndirectParam(GetModuleHandle(0), (LPCDLGTEMPLATEW)res, hh, SS_DP,0);
			return 0;
		}

		HWND hParent = 0;
		vector<shared_ptr<PIANOROLLCALLBACK>> cb;


		class SIDEDRAW
		{
		public:
			int Width = 120;
			D2D1_RECT_F full;

		};


		bool White(int mm)
		{
			mm %= 12;
			if (mm == 0 || mm == 2 || mm == 4 || mm == 5 || mm == 7 || mm == 9 || mm == 11)
				return true;
			return false;
		}

		class TOPDRAW
		{
		public:
			signed int he = 15;
			D2D1_RECT_F full;
		};

		class INFODRAW
		{
		public:
			signed int he = 15;
			D2D1_RECT_F full;
		};

		class HEIGHT
		{
		public:
			int AtPos = 0;
			float nh = 20.0;
		};

		public:
		class TEMPO
		{
		public:
			size_t atm = 0; // at measure
			int BpM = 120;

			void Ser(XML3::XMLElement& e) const
			{
				e.vv("atm").SetValueInt((int)atm);
				e.vv("bpm").SetValueInt((int)BpM);
			}
			void Unser(XML3::XMLElement& e)
			{
				atm = (size_t)e.vv("atm").GetValueInt(0);
				BpM = e.vv("bpm").GetValueInt(120);
			}


			bool operator ==(const TEMPO& kk) const
			{
				if (BpM == kk.BpM)
					return true;
				return false;
			}
			bool operator<(const TEMPO& kk)
			{
				if (atm < kk.atm)
					return true;
				return false;
			}
			wchar_t t[50] = { 0 };
			wchar_t* Txt()
			{
				swprintf_s(t, 50, L"%i BpM", BpM);
				return t;
			}

		};


		class KEY
		{
		public:
			wchar_t t[50];
			size_t atm = 0; // at measure
			signed int k = 0; // -7 to +7
			int m = 0; // 0 major 1 minor

			void Ser(XML3::XMLElement& e) const
			{
				e.vv("atm").SetValueInt((int)atm);
				e.vv("k").SetValueInt((int)k);
				e.vv("m").SetValueInt((int)m);
			}
			void Unser(XML3::XMLElement& e)
			{
				atm = (size_t)e.vv("atm").GetValueInt();
				k = e.vv("k").GetValueInt(0);
				m = e.vv("m").GetValueInt(0);
				CreateScale();
			}




			vector<int> Scale;

			wchar_t* Txt()
			{
				swprintf_s(t, 50, L"K %i%s", k,m == 0 ? L"M" : L"m");
				return t;
			}

			bool operator ==(const KEY& kk) const
			{
				if (k == kk.k && m == kk.m)
					return true;
				return false;
			}
			bool operator<(const KEY& kk)
			{
				if (atm < kk.atm)
					return true;
				return false;
			}

			bool BelongsToScale(int mm)
			{
				if (Scale.empty())
					return true;
				if (std::find(Scale.begin(), Scale.end(), mm % 12) == Scale.end())
					return false;
				return true;
			}
			void CreateScale()
			{
				Scale.clear();
				unsigned int fi = 0x48; // C
				if (k > 0)
					fi = (7 * k) % 12;
				if (k < 0)
					fi = (5 * (-k)) % 12;

				if (m == 1)
					fi -= 3;

				fi = fi % 12;
				if (m == 1)
				{
					Scale.push_back(fi);
					Scale.push_back(fi + 2);
					Scale.push_back(fi + 3);
					Scale.push_back(fi + 5);
					Scale.push_back(fi + 7);
					Scale.push_back(fi + 8);
					Scale.push_back(fi + 11);
				}
				else
					if (m == 0)
					{
						Scale.push_back(fi);
						Scale.push_back(fi + 2);
						Scale.push_back(fi + 4);
						Scale.push_back(fi + 5);
						Scale.push_back(fi + 7);
						Scale.push_back(fi + 9);
						Scale.push_back(fi + 11);

					}
				for (auto& e : Scale)
					e = e % 12;
			}

		};
		class TIME
		{
		public:
			size_t atm = 0;
			int nb = 4;
			bool operator<(const TIME& t)
			{
				if (atm < t.atm)
					return true;
				return false;
			}

			void Ser(XML3::XMLElement& e) const
			{
				e.vv("atm").SetValueInt((int)atm);
				e.vv("nb").SetValueInt((int)nb);
			}
			void Unser(XML3::XMLElement& e)
			{
				atm = (size_t)e.vv("atm").GetValueInt();
				nb = e.vv("nb").GetValueInt(4);
			}

		};

		private:

		class DRAWNBEAT
		{
		public:
			D2D1_RECT_F full;
		};

		class DRAWNMEASURESANDBEATS
		{
		public:
			size_t im = 0;
			D2D1_RECT_F full;
			vector<DRAWNBEAT> Beats;
		};
		vector<DRAWNMEASURESANDBEATS> DrawnMeasures;

		class DRAWPIANO
		{
		public:
			int m = 0;
			D2D1_RECT_F full;
		};
		vector<DRAWPIANO> DrawnPiano;

		enum class TOOL
		{
			AUTO = 0,
			ERASER = 1,
			SINGLE = 2,
			QUANTIZE = 3,
			PAINT = 4,
		};



		class DRAWNNOTES
		{
		public:
			int n;
			D2D1_RECT_F full;
		};
		vector<DRAWNNOTES> DrawedNotes;

		MIDIINHANDLE min;
		int DENOM = 4;
		float HeightScale = 1.0;
		float bw = 60.0f;
		float BarStroke = 1.0;
		float MeasureStroke = 2.0;

		D2D1_COLOR_F bg = { 0,0,0.0f,0.8f };
		D2D1_COLOR_F whitecolor = { 1.0f,1.0f,1.0f,1.0f };
		D2D1_COLOR_F blackcolor = { 0.0f,0.0f,0.0f,1.0f };
		D2D1_COLOR_F sidecolor = { 0,0.1f,0.1f,1.0f };
		D2D1_COLOR_F note1color = { 0.8f,0.8f,0.9f,0.8f };
		D2D1_COLOR_F note2color = { 0.8f,0.9f,0.0f,0.9f };
		D2D1_COLOR_F part1color = { 0.9f,0.9f,0.9f,0.2f };
		D2D1_COLOR_F part2color = { 0.9f,0.9f,0.9f,0.25f };
		D2D1_COLOR_F note3color = { 0.1f,0.2f,0.4f,0.3f };
		D2D1_COLOR_F note4color = { 0.1f,0.2f,0.4f,0.9f };
		D2D1_COLOR_F linecolor = { 0.5f,0.7f,0.3f,0.8f };
		D2D1_COLOR_F snaplinecolor = { 0.3f,0.6f,0.6f,0.8f };
		D2D1_COLOR_F scrollcolor = { 1.0f,1.0f,1.0f,0.3f };
		int Direction = 0; // 0 up, 1 down
		int PianoPosition = 0; // 0 side, 1 bottom
		int PianoStartOctave = 2; // If PianoPosition == 1
		int DefPianoVelocity = 127;
		int DefPianoChannel = 0;
		int FirstNote = 48;
		float ScrollX = 0;
		int PianoOnly = 0; // If 1, only the piano will be drawn

		TOOL Tool = TOOL::AUTO; // 0 Auto, 1 Eraser, 2 Single entry, 3 Quantizer
		bool PartMode = false;

		vector<int> HiddenLayers;

		CComPtr<ID2D1SolidColorBrush> SideBrush;
		CComPtr<ID2D1SolidColorBrush> LineBrush;
		CComPtr<ID2D1SolidColorBrush> WhiteBrush;
		CComPtr<ID2D1SolidColorBrush> BlackBrush;
		CComPtr<ID2D1SolidColorBrush> SnapLineBrush;
		CComPtr<ID2D1SolidColorBrush> ScrollBrush;
		CComPtr<ID2D1SolidColorBrush> NoteBrush1;
		CComPtr<ID2D1SolidColorBrush> NoteBrush2;
		CComPtr<ID2D1SolidColorBrush> NoteBrush3;
		CComPtr<ID2D1SolidColorBrush> NoteBrush4;
		CComPtr<ID2D1SolidColorBrush> PartBrush1;
		CComPtr<ID2D1SolidColorBrush> PartBrush2;
		CComPtr<IDWriteFactory> WriteFactory;
		CComPtr<IDWriteTextFormat> Text;

		int ViewLayers = 1;
		int ViewChannels = 1;
		int ViewVelocity = 1;
		int ViewLiveNotes = 1;
		int LastNoteOver = 0;
		size_t LastNoteOverIdx = (size_t)-1;
		size_t LastBeatOverIdx = (size_t)-1;
		POSITION LastOverHP;

		map<size_t,PART> parts;
		vector<NOTE> notes;
		vector<NOTE> clip;
		stack<vector<NOTE>> undo;
		stack<vector<NOTE>> redo;
		RECT rdr;
		size_t TotalWidthForMusic = 0;
		size_t LeftWidthForMusic = 0;
		vector<HEIGHT> Heights = { HEIGHT() };
		vector<TIME> Times = { TIME() };
		vector<KEY> Keys = { KEY() };
		vector<MARKER> Markers;
		vector<TEMPO> Tempos = { TEMPO() };
		HCURSOR CursorArrow = 0, CursorResize = 0, CursorSelect = 0,CursorErase = 0,CursorResize4,CursorHand;
		unsigned int snapres = 1;
		signed int noteres = -1; // bars 
		SIDEDRAW side;
		TOPDRAW top;
		INFODRAW info;
		int MaxUndoLevel = 100;
		int BarMoving = false;
		int Selecting = false;
		int NextChannel = 0;
		int NextLayer = 0;
		int NextPart = 0;
		shared_ptr<NOTE> GroupDragging = 0;
		NOTE * NoteDragging = 0;
		NOTE * NoteResizing = 0;
		NOTE NoteResizingSt;
		bool ResizingRight = 0; // 1 right, 0 left
		int PianoClicking = false;
		POINT LastClick;
		int PianoNoteClicked = -1;
		POSITION LastClickN;
		D2D1_RECT_F SelectRect;

		CComPtr<ID2D1SolidColorBrush> GetD2SolidBrush(ID2D1RenderTarget * p, D2D1_COLOR_F cc)
		{
			CComPtr<ID2D1SolidColorBrush> b = 0;
			p->CreateSolidColorBrush(cc, &b);
			return b;
		}



		bool SelN(size_t i)
		{
			if (i >= notes.size())
				return false;
			if (notes[i].Selected || (PartMode && notes[i].PartSelected(parts)))
				return true;
			return false;
		}


		POSITION MidiInInsert;
		vector<int> MidiInsCurrent;
		NOTE MidiInsNote1;
		void InsertNoteFromMidiIn(DWORD e)
		{
			if (IsNoteOn(e))
			{
				MidiInsCurrent.push_back(Note(e));
				auto t1 = make_tuple<POSITION, int, NOTE*>(std::forward<POSITION>(MidiInInsert), (e & 0xFFFF) >> 8, std::forward<NOTE*>(&MidiInsNote1));
				LeftDoubleClick(0, 0, &t1);
				return;
			}
			if (IsNoteOff(e))
			{
				auto f = find(MidiInsCurrent.begin(), MidiInsCurrent.end(), Note(e));
				if (f == MidiInsCurrent.end())
					return; // duh
				MidiInsCurrent.erase(f);
				if (MidiInsCurrent.empty())
				{
					MidiInInsert = MidiInsNote1.EndX();
					// Convert it
					for (;;)
					{
						auto ti = TimeAtMeasure(MidiInInsert.m);
						if (ti.nb > MidiInInsert.f.n)
							break;
						MidiInInsert.f.n -= ti.nb;
						MidiInInsert.m++;
					}
				}

			}
		}

		void PushUndo()
		{
			undo.push(notes);
			redo = stack<vector<NOTE>>();
		}

		template <typename T = float> bool InRect(D2D1_RECT_F & r, T x, T y)
		{
			if (x >= r.left && x <= r.right && y >= r.top && y <= r.bottom)
				return true;
			return false;
		}

		DRAWNMEASURESANDBEATS* DrawnMeasureByIndex(size_t idx)
		{
			auto e = std::find_if(DrawnMeasures.begin(), DrawnMeasures.end(), [&](const DRAWNMEASURESANDBEATS & m) -> BOOL
				{
					if (m.im == idx)
						return true;
					return false;
				});
			if (e == DrawnMeasures.end())
				return nullptr;
			return &*e;
		}



	public:

		vector<TIME>& GetTimes() {
			return Times; }
		vector<TEMPO>& GetTempos() { return Tempos; }


		void DestroyBrushes()
		{
			WhiteBrush = 0;
			BlackBrush = 0;
			SideBrush = 0;
			ScrollBrush = 0;
			WhiteBrush = 0;
			BlackBrush = 0;
			LineBrush = 0;
			SnapLineBrush = 0;
			PartBrush1 = 0;
			PartBrush2 = 0;
			NoteBrush1 = 0;
			NoteBrush2 = 0;
			NoteBrush3 = 0;
			NoteBrush4 = 0;
			WriteFactory = 0;
			Text = 0;

		}

		ID2D1RenderTarget* ForBrushes = 0;
		void CreateBrushes(ID2D1RenderTarget* p, bool F = false)
		{
			if (ForBrushes != p)
				DestroyBrushes();
			if (SideBrush && !F)
				return; // OK

			ForBrushes = p;
			SideBrush = GetD2SolidBrush(p, sidecolor);
			ScrollBrush = GetD2SolidBrush(p, scrollcolor);
			WhiteBrush = GetD2SolidBrush(p, whitecolor);
			BlackBrush = GetD2SolidBrush(p, blackcolor);
			LineBrush = GetD2SolidBrush(p, linecolor);
			SnapLineBrush = GetD2SolidBrush(p, snaplinecolor);
			PartBrush1 = GetD2SolidBrush(p, part1color);
			PartBrush2 = GetD2SolidBrush(p, part2color);
			NoteBrush1 = GetD2SolidBrush(p, note1color);
			NoteBrush2 = GetD2SolidBrush(p, note2color);
			NoteBrush3 = GetD2SolidBrush(p, note3color);
			NoteBrush4 = GetD2SolidBrush(p, note4color);

			DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown * *)& WriteFactory);

			LOGFONT lf;
			GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(lf), &lf);
			DWRITE_FONT_STYLE fst = DWRITE_FONT_STYLE_NORMAL;
			if (lf.lfItalic)
				fst = DWRITE_FONT_STYLE_ITALIC;
			DWRITE_FONT_STRETCH fsr = DWRITE_FONT_STRETCH_NORMAL;
			FLOAT fs = (FLOAT)abs(lf.lfHeight);
			WriteFactory->CreateTextFormat(lf.lfFaceName, 0, lf.lfWeight > 500 ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_NORMAL, fst, fsr, fs, L"", &Text);

		}


		static bool IsNoteOn(DWORD e, int* pnot = 0, int* pvel = 0, int* pch = 0)
		{
			if ((e & 0xF0) != 0x90)
				return false;
			int vel = (e & 0xFF0000) >> 16;
			if (vel == 0)
				return false;
			if (pnot)
				* pnot = (e & 0xFF00) >> 8;
			if (pch)
				* pch = (e & 0xF);
			if (pvel)
				* pvel = vel;
			return true;
		}
		static bool IsNoteOff(DWORD e, int* pnot = 0, int* pch = 0)
		{
			if ((e & 0xF0) == 0x80)
			{
				if (pnot)
					* pnot = (e & 0xFF00) >> 8;
				if (pch)
					* pch = (e & 0xF);
				return true;
			}
			if ((e & 0xF0) == 0x90)
			{
				int vel = (e & 0xFF0000) >> 16;
				if (vel == 0)
				{
					if (pnot)
						* pnot = (e & 0xFF00) >> 8;
					if (pch)
						* pch = (e & 0xF);
					return true;
				}
			}
			return false;
		}
		static int Note(DWORD e)
		{
			return (e >> 8) & 0xFF;
		}


		PIANOROLL(HWND hp = 0)
		{
			hParent = hp;
			Keys.resize(1);
			Tempos.resize(1);
			Keys[0].CreateScale();
			CursorResize = LoadCursor(0, IDC_SIZEWE);
			CursorResize4 = LoadCursor(0, IDC_SIZEALL);
			CursorHand = LoadCursor(0, IDC_HAND);
			CursorArrow = LoadCursor(0, IDC_ARROW);
			CursorErase = LoadCursor(0, IDC_NO);
			CursorSelect = LoadCursor(0, IDC_IBEAM);
		}


		void RemoveDups() 
		{
			vector<KEY> nkeys;
			signed int p = 999;
			for (auto& k : Keys)
			{
				if (k.k == p)
					continue;
				p = k.k;
				nkeys.push_back(k);
			}
			Keys = nkeys;


			vector<TIME> ntimes;
			p = 999;
			for (auto& k : Times)
			{
				if (k.nb == p)
					continue;
				p = k.nb;
				ntimes.push_back(k);
			}
			Times = ntimes;

			vector<TEMPO> ntempos;
			p = 999;
			for (auto& k : Tempos)
			{
				if (k.BpM== p)
					continue;
				p = k.BpM;
				ntempos.push_back(k);
			}
			Tempos = ntempos;
		}

		void Ser(XML3::XMLElement& e) const
		{

			e.vv("FirstNote").SetValueInt(FirstNote);

			// Side Perc
			e.vv("SideWidth").SetValueInt(side.Width);

			// View Stuff
			e.vv("ViewLayers").SetValueInt(ViewLayers);
			e.vv("ViewVelocity").SetValueInt(ViewVelocity);
			e.vv("ViewChannels").SetValueInt(ViewChannels);

			// Notes
			auto& ee = e["notes"];
			for (auto& n : notes)
			{
				auto& nn = ee.AddElement("n");
				n.Ser(nn);
			}

			// Times
			auto& tt = e["times"];
			for(auto& t : Times)
			{
				auto& nn = tt.AddElement("t");
				t.Ser(nn);
			}

			// Keys
			auto& kk = e["keys"];
			for (auto& t : Keys)
			{
				auto& nn = kk.AddElement("k");
				t.Ser(nn);
			}

			// Markers
			auto& mm = e["markers"];
			for (auto& t : Markers)
			{
				auto& nn = mm.AddElement("m");
				t.Ser(nn);
			}

			// Tempos
			auto& te = e["tempos"];
			for (auto& t : Tempos)
			{
				auto& nn = te.AddElement("t");
				t.Ser(nn);
			}

			 // Parts
			auto& pa = e["parts"];
			for(auto& p : parts)
			{
				auto& nn = pa.AddElement("p");
				p.second.Ser(p.first,nn);
			}

		}

		void Unser(XML3::XMLElement& e)
		{

			FirstNote = e.vv("FirstNote").GetValueInt(48);

			// Side Perc
			side.Width = e.vv("SideWidth").GetValueInt(150);

			ViewLayers = e.vv("ViewLayers").GetValueInt(1);
			ViewVelocity = e.vv("ViewVelocity").GetValueInt(1);
			ViewChannels = e.vv("ViewChannels").GetValueInt(1);

			// Notes
			notes.clear();
			auto& ee = e["notes"];
			for (auto& eee : ee)
			{
				NOTE n;
				n.Unser(eee);
				notes.push_back(n);
			}
			std::sort(notes.begin(), notes.end());

			// Markers
			for (auto& eee : e["markers"])
			{
				MARKER m;
				m.Unser(eee);
				Markers.push_back(m);
			}
			sort(Markers.begin(), Markers.end());

			// Tempos
			for (auto& eee : e["tempos"])
			{
				TEMPO m;
				m.Unser(eee);
				Tempos.push_back(m);
			}
			sort(Tempos.begin(), Tempos.end());

			// Keys
			for (auto& eee : e["keys"])
			{
				KEY m;
				m.Unser(eee);
				Keys.push_back(m);
			}
			sort(Keys.begin(), Keys.end());

			// Times
			for (auto& eee : e["times"])
			{
				TIME m;
				m.Unser(eee);
				Times.push_back(m);
			}
			sort(Times.begin(), Times.end());

			// Parts
			for (auto& eee : e["parts"])
			{
				PART p;
				parts[(size_t)p.Unser(eee)] = p;
			}

			Redraw();
		}

		void FromMidi(const unsigned char* m, size_t sz,bool TrkToLy = false)
		{
			MIDI mm;
			int tpb = 0;
			map<int, vector<MIDI::MIDIITEM>> mx;
			if (FAILED(mm.ReadMidi(m, sz,tpb, mx)))
				return;
			if (tpb == 0)
				return;

			 // Load it
			map<int,map<int, POSITION>> notesonn;
			unsigned long long AbsTicks = 0;
			for (auto& me : mx)
			{
				int ly = me.first;
				auto& v = me.second;
				for (auto& vv : v)
				{
					auto de = vv.ti.delta;
					AbsTicks += de;

					int BeatIdx = (int)((float)AbsTicks / (float)tpb);
					ABSPOSITION a;
					a.beats = BeatIdx;
					// And the fraction

					// Convert to position
					POSITION p;
					for (size_t im = 0; ; im++)
					{
						auto e = TimeAtMeasure(im);
						if (e.nb <= (int)a.beats)
						{
							a.beats -= e.nb;
							continue;
						}
						p.m = im;
						p.f.n = a.beats;
						p.f.d = DENOM;
						break;
					}

					int not = 0;
					int ch = 0;
					int vel = 0;


					if (IsNoteOn(vv.event,&not,&vel,&ch))
					{
						p.noteht = vel;
						notesonn[ch][not] = p;
						continue;
					}
					if (IsNoteOff(vv.event, &not, &ch))
					{
						POSITION start = notesonn[ch][not];
						notesonn[ch].erase(not);

						NOTE nx;
						nx.ch = ch;
						nx.midi = not;
						nx.vel = start.noteht;
						start.noteht = 0;
						if (TrkToLy)
							nx.layer = ly;
						nx.p = start;
						auto a2 = AbsF(start);
						auto a1 = AbsF(p);
						nx.d = DistanceBetweenAbs(a1, a2);
						notes.push_back(nx);
						continue;

					}

					// Other effect, just put
					if (vv.data.empty())
					{
						NOTE nx;
						if (TrkToLy)
							nx.layer = ly;
						nx.nonote = vv.event;
						nx.midi = 48;
						nx.p = p;
						auto p2 = p;
						p2.m++;
						p2.f.n = 0;
						auto a2 = AbsF(p2);
						auto a1 = AbsF(p);
						nx.d = DistanceBetweenAbs(a2, a1);
						notes.push_back(nx);

					}
					else
					{
						if (vv.ff == 0x59)
						{
							// Key
							if (vv.data.size() == 2)
							{
								KEY k;
								k.k = (char)vv.data[0];
								k.m = (char)vv.data[1];
								Keys.push_back(k);
							}
							continue;
						}
						NOTE nx;
						if (TrkToLy)
							nx.layer = ly;
						nx.midi = 48;
						nx.p = p;
						auto p2 = p;
						p2.m++;
						p2.f.n = 0;
						auto a2 = AbsF(p2);
						auto a1 = AbsF(p);
						nx.d = DistanceBetweenAbs(a2, a1);
						nx.HasMetaEvent = true;
						nx.MetaEvent = vv.ff;
						nx.MetaEventData = vv.data;

						notes.push_back(nx);
					}

				}
			}

			sort(Keys.begin(), Keys.end());
			sort(notes.begin(), notes.end());
			Redraw();
		}

		void SetPianoOnly(bool b)
		{
			PianoOnly = b;
			Redraw();
		}

		set<int> GetLayers()
		{
			set<int> l;

			for (auto& n : notes)
			{
				l.insert(n.layer);
			}
			return l;
		}

		string ToGuidoAll()
		{
			string a = " { ";

			auto ly = GetLayers();
			bool NeedComma = false;
			int iStaff = 1;
			for (auto& l : ly)
			{
				if (NeedComma)
					a += ",";
				a += ToGuido(l,iStaff);
				NeedComma = true;
				iStaff++;
			}
			a += " } ";
			return a;
		}
		string ToGuido(int ly,int iStaff = 1,char* addt = 0)
		{

			auto AddDur = [](FRACTION lp)
			{
				if (lp == FRACTION(1, 1))
					return "/1 ";
				if (lp == FRACTION(1, 2))
					return "/2 ";
				if (lp == FRACTION(1, 4))
					return "/4 ";
				if (lp == FRACTION(1, 8))
					return "/8 ";
				if (lp == FRACTION(1, 16))
					return "/16 ";
				if (lp == FRACTION(1, 32))
					return "/32 ";
				if (lp == FRACTION(1, 64))
					return "/64 ";

				return "";
			};

			// Example:  { [ \staff<1> \clef<"g2"> \meter<"4/4">   { a2, h&,c } g g e d  d/8 d/8 d/4 c   \meter<"3/4"> f/4 g e d d d     _ e g  ] } 
			string x;
			vector<char> fmt(1000);

			// { [ \staff<1>  ( { a, h&0 } ) ]  } 
			x += "[ ";
			if (addt)
				x += addt;
			sprintf_s(fmt.data(), 1000, " \\staff<%i> \\clef<\"g2\"> ( ", iStaff);
			x += fmt.data();

			TIME ti0;
			KEY ke0;
			size_t ni = 0;
			for (size_t im = 0; ; im++)
			{
				auto ti = TimeAtMeasure(im);
				auto ke = KeyAtMeasure(im);
				size_t NotesInThisMeasure = 0;

				// Change Time
				if (ti.nb != ti0.nb || im == 0)
				{
					sprintf_s(fmt.data(), 1000, " \\meter<\"%u/%u\"> ", ti.nb, DENOM);
					x += fmt.data();
					ti0.nb = ti.nb;
				}

				// Change Key
				if (!(ke == ke0) || im == 0)
				{
					sprintf_s(fmt.data(), 1000, " \\key<%i> ", ke.k);
					x += fmt.data();
					ke0 = ke;
				}


				// The following assumes there are no chords
				// For chords, be back later :)
				bool NoMoreNotes = 1;
				POSITION  CurrentP;
				CurrentP.m = im;
				CurrentP.f = FRACTION(0, 1);
				for (size_t i = ni ; i < notes.size(); i++,ni++)
				{
					auto& n1 = notes[i];
					if (n1.layer != ly)
						continue;
					if (n1.p.m < im)
						continue;

					NoMoreNotes = 0;
					if (n1.p.m > im)
					{
						FRACTION fm(ti.nb, DENOM);
						if (CurrentP.f < fm)
						{
							// Put a rest
							x += " _";
							auto lp = fm - CurrentP.f;
							x += AddDur(lp);
						}
						break;
					}

					if (CurrentP < n1.p)
					{
						// Put a rest
						x += " _";
						auto lp = n1.p.f - CurrentP.f;
						x += AddDur(lp);
					}

					// Note
					wchar_t n[10] = { 0 };
					MidiNoteName(n, n1.midi, ke.k, ke.m);
					if (n[1] == L'\u266F')
						n[1] = '#';
					if (n[1] == L'\u266D')
						n[1] = '&';
					n[0] = (wchar_t)tolower(n[0]);
					int oct = n1.midi / 12;
					wchar_t n2[10] = { 0 };
					if (oct >= 5)
						swprintf_s(n2, 10, L"%c", '1' + (oct - 5));
					else
					if (oct == 4)
						swprintf_s(n2, 10, L"0");
					else
						swprintf_s(n2, 10, L"-%c", '1' + (3 - oct));
					wcscat_s(n, 10, n2);
					x += " ";
					x += XML3::XMLU(n);
					CurrentP = n1.EndX();
					x += AddDur(n1.d);

					NotesInThisMeasure++;
				}
				if (NoMoreNotes)
					break;


				if (!NotesInThisMeasure)
				{
					// Insert rest
					for (int j = 0; j < ti.nb; j++)
						x += " _ ";
				}

			}


			x += " ) ]";
			return x;
		}

		void Shift(signed int msr = 0,int NewLayer = -1)
		{
			if (msr == 0)
				return;
			for (auto& k : Times)
				k.atm += msr;
			for (auto& k : Keys)
				k.m += msr;
			for (auto& k : Tempos)
				k.atm += msr;
			for (auto& k : Markers)
				k.p.m += msr;
			for (auto& k : notes)
				k.p.m += msr;

			if (NewLayer >= 0)
			{
				for (auto& k : notes) k.layer = NewLayer;
			}
		}

		void Append(PR::PIANOROLL& p)
		{
			for (auto& k : p.Times)
				Times.push_back(k);
			std::sort(Times.begin(), Times.end());

			for (auto& k : p.Keys)
				Keys.push_back(k);
			std::sort(Keys.begin(), Keys.end());

			for (auto& k : p.Tempos)
				Tempos.push_back(k);
			std::sort(Tempos.begin(), Tempos.end());

			for (auto& k : p.Markers)
				Markers.push_back(k);
			std::sort(Markers.begin(), Markers.end());

			for (auto& k : p.notes)
				notes.push_back(k);
			std::sort(notes.begin(), notes.end());
		}

		void ToMidi(vector<unsigned char>& v, int TPB = 960, std::function<HRESULT(MIDI::MIDIITEM& m)> streamf = nullptr, std::vector<MIDI::MIDIITEM>* mmap = 0,int uSR = 0,bool NO = false,std::vector<std::vector<MIDI::MIDIITEM>>* mmore = 0)
		{
			MIDI m;
			map<int, vector<MIDI::MIDIITEM>> s;


			if (!NO)
			{
				// Keys
				for (auto& k : Keys)
				{
					MIDI::MIDIITEM it1;
					it1.Key(k.k, k.m);
					POSITION ps;
					ps.m = k.atm;
					auto ti = AbsF(ps);
					it1.ti.abs = ti.ToTpb(TPB);
					s[0].push_back(it1);
				}

				// Tempos
				for (auto& k : Tempos)
				{
					MIDI::MIDIITEM it1;
					it1.Tempo(k.BpM);
					POSITION ps;
					ps.m = k.atm;
					auto ti = AbsF(ps);
					it1.ti.abs = ti.ToTpb(TPB);
					s[0].push_back(it1);
				}

				// Times
				for (auto& k : Times)
				{
					MIDI::MIDIITEM it1;
					it1.Time(k.nb, 4);
					POSITION ps;
					ps.m = k.atm;
					auto ti = AbsF(ps);
					it1.ti.abs = ti.ToTpb(TPB);
					s[0].push_back(it1);
				}

				// Markers
				for (auto& mm : Markers)
				{
					MIDI::MIDIITEM it1;
					it1.Marker(mm.t.c_str());
					auto ti = AbsF(mm.p);
					it1.ti.abs = ti.ToTpb(TPB);
					s[0].push_back(it1);
				}
			}

			// Notes
			for (size_t in = 0 ; in < notes.size() ; in++)
			{
				auto& n = notes[in];
				if (n.HasMetaEvent)
				{
					MIDI::MIDIITEM it1;
					it1.stridx = in;
					it1.event = 0;
					it1.ff = n.MetaEvent;
					it1.data = n.MetaEventData;
					it1.ti.abs = 0;
					auto ti = AbsF(n.p);
					it1.ti.abs = ti.ToTpb(TPB);
					if (streamf || uSR)
						s[0].push_back(it1);
					else
						s[n.layer + 1].push_back(it1);
					continue;
				}
				if (n.nonote > 0)
				{
					MIDI::MIDIITEM it1;
					it1.stridx = in;
					it1.event = 0;
					it1.event = n.nonote;
					it1.ti.abs = 0;

					// Find absolute time 
					auto ti = AbsF(n.p);
					it1.ti.abs = ti.ToTpb(TPB);

					if (streamf || uSR)
						s[0].push_back(it1);
					else
						s[n.layer + 1].push_back(it1);
					continue;
				}

				MIDI::MIDIITEM it1; 
				it1.stridx = in;
				it1.event = 0;
				it1.event = 0x90;
				it1.event |= n.ch;
				it1.event |= (n.vel << 16);
				it1.event |= (n.midi << 8);
				it1.ti.abs = 0; 

				// Find absolute time 
				auto ti = AbsF(n.p);
				it1.ti.abs = ti.ToTpb(TPB);

				if (streamf || uSR)
					s[0].push_back(it1);
				else
					s[n.layer + 1].push_back(it1);

				MIDI::MIDIITEM it2; 
				it2.stridx = in;
				it2.event = it1.event;
				it2.event &= 0xFFFF;
				auto nend = n.EndX();
				auto ti2 = AbsF(nend);
				it2.ti.abs = ti2.ToTpb(TPB);

				if (streamf || uSR)
					s[0].push_back(it2);
				else
					s[n.layer + 1].push_back(it2);
			}

			if (streamf)
			{
				sort(s[0].begin(), s[0].end());
				for (auto& ss : s[0])
				{
					auto e = streamf(ss);
					if (FAILED(e))
						break;
				}
				return;
			}

			for (auto& ss : s)
			{
				sort(ss.second.begin(), ss.second.end());
			}
			if (uSR)
			{
				for (auto& ss : s)
				{
					int b = 120;
					for (auto& sss : ss.second)
					{
						auto te = sss.GetTempo();
						sss.ti.smpl = sss.ti.ToSamples(TPB, b, uSR);
						if (te)
							b = te;
					}
				}

			}
			vector<vector<MIDI::MIDIITEM>> TrackData;
			for (auto& ss : s)
			{
				TrackData.push_back(ss.second);
			}

			if (mmore)
			{
				for (auto& mm : *mmore)
					TrackData.push_back(mm);
			}

			if (mmap)
			{
				for (auto& ss : s)
					mmap->insert(mmap->end(),ss.second.begin(),ss.second.end());
				std::sort(mmap->begin(),mmap->end());
			}
			m.Write(1, TPB, TrackData, v);
		}

		void SetWindow(HWND hp)
		{
			hParent = hp;
		}
		void Undo()
		{
			if (undo.empty())
				return;
			redo.push(notes);
			notes = undo.top();
			undo.pop();
			Redraw();
		}

		void Redo()
		{
			if (redo.empty())
				return;
			undo.push(notes);
			notes = redo.top();
			redo.pop();
			Redraw();
		}


		HRESULT EnsureVisible(size_t im)
		{
			if (im >= notes.size())
				return E_INVALIDARG;
			auto& nn = notes[im];
			if (nn.dr.left >= rdr.right || nn.dr.right <= rdr.left)
			{
				ScrollX = PositionToX(nn.p, true);
				Redraw();
			}
			return S_OK;
		}
		HRESULT SelectNote(size_t im,int S)
		{
			if (im >= notes.size())
				return E_INVALIDARG;
			auto& nn = notes[im];
			if (nn.Selected == S)
				return S_FALSE;
			nn.Selected = S;
			Redraw();
			return S_OK;
		}

		void Redraw(unsigned long long p = 0)
		{
			if (BlackBrush == 0)
				return; // not yet
			for (auto c : cb)
				c->RedrawRequest(this, p);
		}


		vector<shared_ptr<PIANOROLLCALLBACK>>& Callbacks() { return cb; }


		void DestroyCallbacks()
		{
			cb.clear();
		}

		void AddCallback(shared_ptr<PIANOROLLCALLBACK> c)
		{
			cb.push_back(c);
		}


		size_t AbsMeasure(size_t im)
		{
			size_t nb = 0;
			for (size_t i = 0; i < im; i++)
			{
				auto t = TimeAtMeasure(i);
				nb += t.nb;
			}
			return nb;
		}

		FRACTION DistanceBetweenAbs(ABSPOSITION& a1, ABSPOSITION& a2)
		{
			ssize_t b1 = a1.beats;
			ssize_t b2 = a2.beats;
			ssize_t b3 = b1 - b2;
			FRACTION f(b3,DENOM);
			f += (a1.f - a2.f);
			return f;
		}


		ABSPOSITION AbsF(POSITION& p)
		{
			ABSPOSITION x;
			x.beats = AbsMeasure(p.m);
			FRACTION f = p.f;
			f.simplify();
			FRACTION f1(1, DENOM);
			while (f >= f1)
			{
				f -= f1;
				x.beats++;
			}
			x.f = f;
			x.f.simplify();
			return x;
		}

		POSITION MeasureAndBarHitTest(float width, bool Precise = false,size_t* didx = 0)
		{
			POSITION np;
			np.m = (size_t)-1;

			for (size_t ii = 0 ; ii < DrawnMeasures.size() ; ii++)
			{
				auto& dd = DrawnMeasures[ii];

				if (dd.full.left > width)
					continue;
				if (dd.full.right <= width)
					continue;

				// This is it
				np.m = dd.im;
				for (size_t y = 0; y < dd.Beats.size(); y++)
				{
					auto& b = dd.Beats[y];
					if (b.full.left > width)
						continue;
					if (b.full.right < width)
						continue;
					//				np.beatht = y;

									// Calculate Also the fraction
					if (Precise)
					{
						np.f.d = (int)(dd.full.right - dd.full.left);
						np.f.n = (int)(width - dd.full.left);
						break;
					}
					else
					{
						size_t TotBeats = dd.Beats.size() * snapres;
						np.f.d = DENOM * snapres;
						float widthpersnap = (dd.full.right - dd.full.left) / TotBeats;
						for (size_t nn = 0; nn < TotBeats ; nn++)
						{
							if (width >= ((nn * widthpersnap) + dd.full.left))
								np.f.n = nn;
							else
								break;
						}
					}

					if (didx)
						* didx = ii;
					return np;
				}
			}

			if (didx)
				*didx = (size_t)-1;
			return np;
		}

		int MidiHitTest(float height,size_t* pidx = 0)
		{
			for (size_t i = 0; i < DrawedNotes.size(); i++)
			{
				auto& dd = DrawedNotes[i];
				if (dd.full.top > height)
					continue;
				if (dd.full.bottom < height)
					continue;

				if (pidx)
					*pidx = i;
				return dd.n;
			}
			return -1;
		}

		float HeightAtNote(int)
		{
			if (Heights.size() == 1)
				return Heights[0].nh * HeightScale;

			return 0.0f; //*
		}

		ssize_t PartHitTest(float width,float height)
		{
			for(auto& p : parts)
			{
				if (InRect(p.second.full,width, height))
					return p.first;
			}
			return -1;
		}


		size_t FindEmptyPart()
		{
			if (parts.empty())
			{
				parts[0].n = L"";
				return 0;
			}
			return parts.rbegin()->first + 1;
		}

		void InvalidatePart(size_t ip = (size_t)-1)
		{
			if (!PartMode)
				return;
			if (ip == (size_t)-1)
			{
				if (parts.empty())
					parts[0].n = L"";
				for (auto& p : parts)
				{
					FindPartRect(p.first);
				}
			}
			else
				FindPartRect(ip);
		}


		void FindPartRect(size_t ip)
		{
			auto& p = parts[ip];
			p.full = { 0,0,0,0 };
			for (auto& n : notes)
			{
				if (n.part != ip)
					continue;

				if (p.full.right == 0)
					p.full = n.dr;

				if (n.dr.right == 0)
					continue;

				if (n.dr.left < p.full.left)
					p.full.left = n.dr.left;
				if (n.dr.right > p.full.right)
					p.full.right = n.dr.right;
				if (n.dr.top < p.full.top)
					p.full.top = n.dr.top;
				if (n.dr.bottom > p.full.bottom)
					p.full.bottom = n.dr.bottom;
			}
		}


		vector<NOTE>& GetNotes() { return notes;  }

		FRACTION MillisecondsForMeasure(size_t im)
		{
			FRACTION f(0, 1);
			auto ti = TimeAtMeasure(im);
			auto te = TempoAtMeasure(im);
			f.Set(ti.nb*1000*60,te.BpM);
			f.simplify();
			return f;
		}

		FRACTION MillisecondsForDuration(size_t im,const FRACTION& dur)
		{
			FRACTION f(0, 1);
			auto f2 = MillisecondsForMeasure(im);
			auto ti = TimeAtMeasure(im);
			FRACTION nbx(ti.nb, DENOM);
			// In nbx  , f2 ms
			// In nn.d  ?

			f.Set(dur.n * nbx.d * f2.n, dur.d * nbx.n * f2.d);
			f.simplify();
			return f;
		}

		FRACTION MillisecondsForNote(size_t n)
		{
			FRACTION f(0, 1);
			if (n >= notes.size())
				return f;
			auto& nn = notes[n];
			auto im = nn.p.m;
			return MillisecondsForDuration(im, nn.d);
		}

		TIME TimeAtMeasure(size_t im)
		{
			TIME tt;
			for (auto& t : Times)
			{
				if (t.atm <= im)
					tt = t;
			}
			return tt;
		}

		KEY KeyAtMeasure(size_t im)
		{
			KEY tt;
			for (auto& k : Keys)
			{
				if (k.atm <= im)
					tt = k;
			}
			return tt;
		}

		TEMPO TempoAtMeasure(size_t im)
		{
			TEMPO tt;
			for (auto& k : Tempos)
			{
				if (k.atm <= im)
					tt = k;
			}
			return tt;
		}


		D2D1_RECT_F NotePos(int n)
		{
			D2D1_RECT_F d;

			d.left = (FLOAT)rdr.left;
			d.right = (FLOAT)rdr.right;

			if (Direction == 0)
			{
				float NoteBottomX = (FLOAT)rdr.bottom;
				if (n < FirstNote)
				{
					DebugBreak();
				}
				for (auto j = FirstNote; j < n; j++)
				{
					NoteBottomX -= HeightAtNote(j);
				}
				float NoteTopX = NoteBottomX - HeightAtNote(n);
				d.bottom = NoteBottomX;
				d.top = NoteTopX;
			}
			if (Direction == 1)
			{
				float NoteTopX = (FLOAT)rdr.top;
				NoteTopX += (top.full.bottom - top.full.top);
				NoteTopX += (info.full.bottom - info.full.top);
				for (auto j = FirstNote; j < n; j++)
					NoteTopX += HeightAtNote(j);
				float NoteBottomX = NoteTopX + HeightAtNote(n);
				d.bottom = NoteBottomX;
				d.top = NoteTopX;
			}


			return d;
		}

		signed int PitchShift(DWORD ev)
		{
			ev >>= 8;
			ev &= 0xFFFF;

			int lsb = ev & 0xFF;
			int msb = (ev >> 8) & 0xFF;

			int g = lsb + (msb * 128);
			return g;
		}

		int PitchShiftR(int b)
		{
			int low7 = b & 0x7F;
			b >>= 7;
			int high7 = b & 0x7F;
			return (high7 << 8) | low7;
		}

		size_t NoteAtPos(int x, int y, bool ResizeEdge = false, bool* Right = 0,bool IgnoreLayer = 0)
		{
			/*		bool Shift = ((GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0);
					if (Shift)
						DebugBreak();
			*/
			for (size_t i = 0; i < notes.size(); i++)
			{
				auto& n = notes[i];
				if (IgnoreLayer == false && n.layer != NextLayer)
					continue;
				if (ResizeEdge)
				{
					if (abs(n.dr.left - x) > 5 && abs(n.dr.right - x) > 5)
						continue;
					if (Right)
					{
						*Right = false;
						if (abs(n.dr.right - x) < 5)
							* Right = true;
					}

				}
				else
				{
					if (n.dr.left > x)
						continue;
					if (n.dr.right < x)
						continue;
				}
				if (n.dr.top > y)
					continue;
				if (n.dr.bottom < y)
					continue;
				return i;
			}
			return (size_t)-1;
		}

		void KeyDown(WPARAM ww, LPARAM = 0, bool S = false, bool C = false, bool A = false)
		{
			bool Shift = ((GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0);
			bool Control = ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0);
			bool Alt = ((GetAsyncKeyState(VK_MENU) & 0x8000) != 0);
			if (S)
				Shift = true;
			if (C)
				Control = true;
			if (A)
				Alt = true;

			if (ww == 219 || ww == 221)
			{
				// Prev, Next marker
				if (Markers.empty())
					return;
				auto e1 = MeasureAndBarHitTest(Direction == 0 ? side.Width + ScrollX : ScrollX + 1);

				if (ww == 221)
				{
					for (size_t i = 0; i < Markers.size(); i++)
					{
						if (Markers[i].p < e1)
							continue;
						if (Markers[i].VisiblePos > 0)
							continue;

						ScrollX = PositionToX(Markers[i].p, true);
						Redraw();
						return;
					}
				}
				else
				{
					for (ssize_t i = Markers.size() - 1; i >= 0; i--)
					{
						if (Markers[i].p > e1)
							continue;
						if (Markers[i].VisiblePos > 0)
							continue;

						ScrollX = PositionToX(Markers[i].p, true);
						Redraw();
						return;
					}

				}
//				Redraw();
				return;
			}

			if (ww == VK_INSERT)
			{
				MARKER m;
				m.p = LastClickN;

				for (size_t i = 0; i < Markers.size(); i++)
				{
					if (Markers[i].p == m.p)
					{
						Markers.erase(Markers.begin() + i);
						Redraw();
						return;
					}
				}
				vector<wchar_t> re(1000);
				if (!AskText(hParent, L"Marker", L"Enter marker name:", re.data()))
					return;
				m.t = re.data();
				Markers.push_back(m);
				sort(Markers.begin(), Markers.end());
				Redraw();
			}

			if (ww == VK_TAB)
			{
				if (PartMode)
				{
					int f = 0;
					if (Shift)
					for (auto rit = parts.rbegin(); rit != parts.rend(); ++rit)
					{
						if (f == 1)
						{
							rit->second.S = true;
							break;
						}

						if (rit->second.S)
						{
							if (f == 0)
							{
								rit->second.S = false;
								f = 1;
								continue;
							}
						}
					}
					else
					for (auto rit = parts.begin(); rit != parts.end(); ++rit)
					{

						if (f == 1)
						{
							rit->second.S = true;
							break;
						}

						if (rit->second.S)
						{
							if (f == 0)
							{
								rit->second.S = false;
								f = 1;
								continue;
							}
						}
					}
					Redraw();
				}
				else
				{
					if (Shift)
					{
						// Select next
						for (ssize_t i = notes.size() - 1; i >= 0; i--)
						{
							if (!notes[i].Selected)
								continue;
							notes[i].Selected = false;
							if (i > 0)
								notes[i - 1].Selected = true;
							else
								notes[notes.size() - 1].Selected = true;
							break;
						}
					}
					else
					{
						// Select next
						for (size_t i = 0; i < notes.size(); i++)
						{
							if (!notes[i].Selected)
								continue;
							notes[i].Selected = false;
							if (i < (notes.size() - 1))
								notes[i + 1].Selected = true;
							else
								notes[0].Selected = true;
							break;
						}
					}
				}
				Redraw();
			}

			if (ww == VK_HOME)
			{
				if (Control)
				{
					ScrollX = 0;
					Redraw();
				}
			}

			if (ww == VK_UP || ww == VK_DOWN)
			{
				if (Shift)
				{
					bool R = false;
					for (size_t i = 0; i < notes.size(); i++)
					{
						if (!SelN(i))
							continue;
						if (notes[i].layer != NextLayer)
							continue;

						if (!R)
							PushUndo();
						R = true;
						if (ww == VK_UP)
							notes[i].ch++;
						if (ww == VK_DOWN)
							notes[i].ch--;

						if (notes[i].ch < 0 || notes[i].ch > 15)
							notes[i].ch = 0;

					}
					if (R)
						Redraw();
					return;
				}
				if (Alt)
				{
					bool R = false;
					for (size_t i = 0; i < notes.size(); i++)
					{
						if (!SelN(i))
							continue;
						if (!R)
							PushUndo();
						R = true;
						if (ww == VK_UP)
							notes[i].layer++;
						if (ww == VK_DOWN)
							notes[i].layer--;

						if (notes[i].layer < 0)
							notes[i].layer = 0;
					}
					if (R)
						Redraw();
					return;
				}
			}

			if (ww == 191) // /
			{
				bool R = false;
				// Split notes
				for (size_t i = 0; i < notes.size(); i++)
				{
					if (!notes[i].Selected)
						continue;
					if (notes[i].layer != NextLayer)
						continue;

					auto e = notes[i].EndX();
					int U = DENOM * snapres;
					if (!R)
						PushUndo();
					R = true;
					notes[i].d += FRACTION(1, U);

				}
				if (R)
					Redraw();
				return;

			}

			if (ww == 'D' || ww == 'H' || ww == 222) // Double/Half/Dot
			{
				bool R = false;
				for (size_t i = 0; i < notes.size(); i++)
				{
					if (!notes[i].Selected)
						continue;
					if (notes[i].layer != NextLayer)
						continue;
					if (!R)
						PushUndo();
					R = true;
					if (ww == 'D')
						notes[i].d.n *= 2;
					if (ww == 'H')
						notes[i].d.d *= 2;
					if (ww == 222)
					{
						notes[i].d.n *= 3;
						notes[i].d.d *= 2;
					}
				}
				if (R)
					Redraw();
				return;
			}

			if (ww == 'Q' && Control) // Quantize
			{
				bool R = false;
				for (size_t i = 0; i < notes.size(); i++)
				{
					if (notes[i].layer != NextLayer)
						continue;
					if (!SelN(i))
						continue;
					if (!R)
						PushUndo();
					R = true;
					Quantize(notes[i]);
				}
				if (R)
					Redraw();
				return;
			}

			if ((ww == 'X'  || ww == 'Z') && !Control) // Move Left/Right
			{
				bool R = false;
				for (size_t i = 0; i < notes.size(); i++)
				{

					if (!SelN(i))
						continue;
					if (notes[i].layer != NextLayer)
						continue;

					if (!R)
						PushUndo();
					R = true;

					// Change position
					auto& p = notes[i].p;
					if (ww == 'X')
					{
						auto tt = TimeAtMeasure(p.m);
						p.f += FRACTION(1, DENOM*snapres);
						if (tt.nb <= (p.f.n/(p.f.d/DENOM)))
						{
							p.m++;
							p.f.n = 0;
						}
					}
					else
					{
						p.f -= FRACTION(1, DENOM * snapres);
						if (p.f.n < 0)
						{
							if (p.m > 0)
							{
								p.m--;
								auto tt = TimeAtMeasure(p.m);
								tt.nb *= snapres;
								p.f = FRACTION(tt.nb - 1, DENOM * snapres);
							}
							else
							{
								p.m = 0;
								p.f.n = 0;
							}
						}
					}

				}
				if (R)
					Redraw();
				return;
			}


			if (ww == 'T' && Control && !Alt) // Transpose Diatonically
			{
				vector<wchar_t> re(1000);
				if (!Shift)
				{
					if (!AskText(hParent, L"Transpose", L"Enter notes:", re.data()))
						return;
				}
				else
				{
					if (!AskText(hParent, L"Transpose", L"Enter semitones:", re.data()))
						return;
				}
				signed int in = _wtoi(re.data());
				if (in == 0)
					return;
				bool R = false;
				for (size_t i = 0; i < notes.size(); i++)
				{
					if (!SelN(i))
						continue;
					if (notes[i].layer != NextLayer)
						continue;
					if (!R)
						PushUndo();
					R = true;

					KEY k = KeyAtMeasure(notes[i].p.m);
					for (int j = 0; j < abs(in); j++)
					{
						for (;;)
						{
							if (in < 0)
							{
								if (notes[i].midi > 0)
									notes[i].midi--;
							}
							else
							{
								if (notes[i].midi < 127)
									notes[i].midi++;
							}
							if (Shift)
								break;
							if (k.BelongsToScale(notes[i].midi))
								break;
						}
					}
				}

				if (R)
					Redraw();
				return;
			}


			if (ww == 220) // back slash
			{
				bool R = false;
				for (size_t i = 0; i < notes.size(); i++)
				{
					if (!notes[i].Selected)
						continue;
					if (notes[i].layer != NextLayer)
						continue;

					auto e = notes[i].EndX();
					int U = DENOM * snapres;
					if (!R)
						PushUndo();
					R = true;
					notes[i].d -= FRACTION(1, U);
					if (notes[i].d.n <= 0)
						notes[i].d += FRACTION(1, U);

				}
				if (R)
					Redraw();
				return;
			}

			if (ww == 'S')
			{
				vector<NOTE> add;
				bool R = false;
				// Split notes
				for (size_t i = 0; i < notes.size(); i++)
				{
					if (!notes[i].Selected)
						continue;
					if (notes[i].layer != NextLayer)
						continue;

					// Change duration
					// If there is a beat, cut it there
					// Else half
					if (!R)
						PushUndo();
					R = true;
					auto n2 = notes[i];


				}

				if (add.empty())
					return;
				notes.insert(notes.end(), add.begin(), add.end());
				std::sort(notes.begin(), notes.end());
				Redraw();
				return;
			}

			if (ww == 'J')
			{
				bool R = false;


				// Join notes
				for (size_t i = 0; i < notes.size(); i++)
				{
					if (!notes[i].Selected)
						continue;
					if (notes[i].layer != NextLayer)
						continue;
					for (size_t y = (i + 1); y < notes.size(); y++)
					{
						if (!notes[y].Selected)
							continue;
						if (notes[y].layer != NextLayer)
							continue;

						if (notes[i].midi != notes[y].midi)
							continue;

						if (notes[i].layer != notes[y].layer)
							continue;

						// Check gap
						auto p1 = notes[i].EndX();
						auto a1 = AbsF(p1);
						auto a2 = AbsF(notes[y].p);
						if (a1 != a2)
							continue;

						if (!R)
							PushUndo();
						notes[i].d += notes[y].d;
						notes.erase(notes.begin() + y);
						R = true;
						break;
					}
				}

				if (!R && PartMode)
				{
					// Join parts
					ssize_t fp = -1;
					for (auto& p : parts)
					{

						if (!p.second.S)
							continue;
						if (fp == -1)
						{
							fp = p.first;
							continue;
						}
						if (!R)
							PushUndo();
						R = true;
						
						for (auto& nn : notes)
						{
							if (NextLayer != nn.layer)
								continue;
							if (nn.part == p.first)
								nn.part = fp;
						}
					}

				}
				if (R)
					Redraw();
				return;
			}


			if (ww >= '1' && ww <= '8')
			{
				if (Control)
				{
					snapres = (unsigned int)ww - '1' + 1;
					Redraw();
					return;
				}
			}

			if (ww >= VK_NUMPAD1 && ww <= VK_NUMPAD9)
			{
				if (!Control && !Shift && !Alt)
				{
					NextLayer = (int)(ww - VK_NUMPAD1);

					auto it = std::lower_bound(HiddenLayers.begin(), HiddenLayers.end(), NextLayer);
					if (it != HiddenLayers.end() && *it == NextLayer)
					{
						HiddenLayers.erase(it);
					}
					Redraw();
					return;
				}
			}
			if (ww >= VK_NUMPAD1 && ww <= VK_NUMPAD9)
			{
				if (!Control && !Shift && Alt)
				{
					// Show/Hide layers
					int li = (int)(ww - VK_NUMPAD1);
					auto it = std::lower_bound(HiddenLayers.begin(), HiddenLayers.end(), li);
					if (it != HiddenLayers.end() && *it == li)
					{
						HiddenLayers.erase(it);
					}
					else
					{
						HiddenLayers.push_back((int)li);
						std::sort(HiddenLayers.begin(), HiddenLayers.end());
					}
					Redraw();
					return;
				}
			}


			if (ww >= '1' && ww <= '8')
			{
				if (!Control && !Shift && !Alt)
				{
					if (ww == '1') noteres = -1;
					if (ww == '2') noteres = -2;
					if (ww == '3') noteres = -3;
					if (ww == '4') noteres = -4;
					if (ww == '5') noteres = -5;
					if (ww == '6') noteres = -6;
					if (ww == '7') noteres = -7;
					if (ww == '8') noteres = -8;
					Redraw();
					return;
				}
			}

			if (ww >= '1' && ww <= '8')
			{
				if (Shift)
				{
					if (ww == '2') noteres = 2;
					if (ww == '3') noteres = 3;
					if (ww == '4') noteres = 4;
					if (ww == '5') noteres = 5;
					if (ww == '6') noteres = 6;
					if (ww == '7') noteres = 7;
					if (ww == '8') noteres = 8;
					Redraw();
					return;
				}
			}


			if (ww == 'A' && Control)
			{
				for (auto& n : notes)
				{
					if (n.layer != NextLayer)
						continue;
					n.Selected = true;
				}
				Redraw();
				return;
			}
			if (ww == 'V' && Control)
			{
				Paste();
				return;
			}
			if (ww == 'C' && Control)
			{
				clip.clear();
				for (auto& n : notes)
				{
					if (n.layer != NextLayer)
						continue;
					if (n.Selected || n.PartSelected(parts))
					{
						clip.push_back(n);
						n.Selected = false;
					}
				}
				Redraw();
				return;
			}
			if (ww == 'Z' && Control)
			{
				Undo();
				return;
			}
			if (ww == 'Y' && Control)
			{
				Redo();
				return;
			}
			if (ww == VK_RIGHT)
			{
				ScrollX += bw;
				Redraw();
				return;
			}
			if (ww == VK_LEFT)
			{
				if (ScrollX >= bw)
					ScrollX -= bw;
				else
					ScrollX = 0;
				Redraw();
				return;
			}
			if (ww == VK_UP)
			{
				if (FirstNote >= 110)
					return;
				FirstNote++;
				if (!White(FirstNote))
					FirstNote++;
				Redraw();
				return;
			}
			if (ww == VK_DOWN)
			{
				if (FirstNote <= 0)
					return;
				FirstNote--;
				if (!White(FirstNote))
					FirstNote--;
				Redraw();
				return;
			}
			if (ww == VK_MULTIPLY)
			{
				HeightScale = 1.0f;
				bw = 60;
				Redraw();
				return;
			}


			if (ww == 188 || ww == 190)
			{
				bool R = false;
				bool U = false;
				for (auto& n : notes)
				{
					if (n.layer != NextLayer)
						continue;
					if (n.Selected || n.PartSelected(parts))
					{
						NOTE nn = n;
						if ((n.nonote & 0xF0) == 0xE0)
						{
							int e = PitchShift(n.nonote);
							if (!Control && !Shift && !Alt)
							{
								if (ww == 190)
									e += 20;
								if (ww == 188)
									e -= 20;
							}
							if (!Control && Shift && !Alt)
							{
								if (ww == 190)
									e += 5;
								if (ww == 188)
									e -= 5;
							}
							if (Control && !Shift && !Alt)
							{
								if (ww == 190)
									e += 50;
								if (ww == 188)
									e -= 50;
							}
							if (Control && Shift && !Alt)
							{
								if (ww == 190)
									e = 0x4000;
								if (ww == 188)
									e = 0;
							}
							if (Alt)
								e = 0x2000;
							if (e < 0)
								e = 0;
							if (e > 0x4000)
								e = 0x4000;

							nn.nonote = (n.nonote & 0xFF) | (PitchShiftR(e) << 8);
						}
						else
						{
							if (Control && ww == 188)
								nn.vel = 0;
							if (Control && ww == 190)
								nn.vel = 127;
							if (!Shift && nn.vel >= 5 && ww == 188)
								nn.vel -= 5;
							if (Shift && nn.vel > 0 && ww == 188)
								nn.vel--;
							if (Shift && nn.vel < 127 && ww == 190)
								nn.vel++;
							if (!Shift && nn.vel < 123 && ww == 190)
								nn.vel += 5;
						}

						if (nn.nonote > 0 && ((nn.nonote & 0xF0) == 0xA0))
						{
							nn.nonote &= 0xFFFF;
							nn.nonote |= (nn.vel << 16);
						}

						for (auto c : cb)
						{
							if (FAILED(c->OnNoteChange(this, &n, &nn)))
								return;
						}
						if (!U)
							PushUndo();
						U = true;
						R = true;
						n.vel = nn.vel;
						if ((n.nonote & 0xF0) == 0xE0)
							n.nonote = nn.nonote;
					}
				}
				if (R)
					Redraw();
				return;
			}

			if (ww == 'P' && !Shift && !Control && !Alt)
			{
				PartMode = !PartMode;
				Redraw();
			}
			if (ww == 'P' && Shift && !Control && !Alt)
			{
				vector<wchar_t> re(1000);
				if (!AskText(hParent, L"Part name", L"Enter part name:", re.data()))
					return;

				for (auto& p : parts)
				{
					if (p.second.S)
						p.second.n = re.data();

				}

				Redraw();
			}
			if (ww == 'P' && !Shift && !Control && Alt)
			{
				vector<wchar_t> re(1000);
				if (!AskText(hParent, L"Part", L"Enter next part:", re.data()))
					return;
				auto ip = _wtoi(re.data());
				if (ip != 0)
					ip--;
				if (ip < 0)
					return;
				NextPart = ip;
				parts[ip].n = L"";
				Redraw();
				return;
			}



			if (ww == 'A' && !Shift && !Control && !Alt)
			{
				Tool = TOOL::AUTO;
				Redraw();
			}
			if (ww == 'E' && !Shift && !Control && !Alt)
			{
				Tool = TOOL::ERASER;
				Redraw();
			}
			if (ww == 'I' && !Shift && !Control && !Alt)
			{
				Tool = TOOL::SINGLE;
				Redraw();
			}
			if (ww == 'Q' && !Shift && !Control && !Alt)
			{
				Tool = TOOL::QUANTIZE;
				Redraw();
			}
			if (ww == 'N' && !Shift && !Control && !Alt)
			{
				Tool = TOOL::PAINT;
				Redraw();
			}
			if (ww == 'G' && !Shift && Control && !Alt)
			{
				vector<wchar_t> re(1000);
				if (!AskText(hParent, L"Measure", L"Enter measure to go:", re.data()))
					return;
				POSITION p;
				p.m = _wtoi(re.data());
				if (p.m > 0)
					p.m--;
				ScrollX = PositionToX(p, true);
				Redraw();
				return;
			}

			if (ww == VK_ADD || ww == VK_SUBTRACT || ww == VK_OEM_PLUS || ww == VK_OEM_MINUS)
			{
				bool R = false;
				bool U = false;
				for (auto& n : notes)
				{
					if (n.layer != NextLayer)
						continue;
					if (n.Selected || n.PartSelected(parts))
					{
						KEY k = KeyAtMeasure(n.p.m);
						NOTE nn = n;
						if ((ww == VK_ADD || ww == VK_OEM_PLUS))
						{
							if (Shift)
								nn.midi++;
							else
							{
								for (;;)
								{
									nn.midi++;
									if (k.BelongsToScale(nn.midi))
										break;
								}
							}
						}
						if ((ww == VK_SUBTRACT || ww == VK_OEM_MINUS))
							if (Shift)
								nn.midi--;
							else
							{
								for (;;)
								{
									nn.midi--;
									if (k.BelongsToScale(nn.midi))
										break;
								}
							}
						if (nn.midi < 0)
							nn.midi = 0;
						if (nn.midi > 127)
							nn.midi = 127;
						if (n.midi == nn.midi)
							continue;
						for (auto c : cb)
						{
							if (FAILED(c->OnNoteChange(this, &n, &nn)))
								return;
						}
						if (!U)
							PushUndo();
						U = true;
						R = true;
						n.midi = nn.midi;
					}
				}
				if (!R)
				{
					// No Note selected, so zoom
					if (Shift)
					{
						if (ww == VK_ADD || ww == VK_OEM_PLUS)
							HeightScale += 0.1f;
						if (ww == VK_SUBTRACT || ww == VK_OEM_MINUS)
						{
							if (HeightScale > 0.4f)
								HeightScale -= 0.1f;
						}
					}
					else
					{
						float ScrollXX = (float)ScrollX / (float)bw;
						if (ww == VK_ADD || ww == VK_OEM_PLUS)
							bw += 10;
						if (ww == VK_SUBTRACT || ww == VK_OEM_MINUS)
						{
							if (bw > 10)
								bw -= 10;
						}
						ScrollX = ScrollXX * (float) bw;
					}
				}
				Redraw();
				return;

			}
			if (ww == VK_DELETE)
			{
				bool R = false;
				bool U = false;
				for (size_t i = 0; i < notes.size(); i++)
				{
					if (notes[i].layer != NextLayer)
						continue;
					if (!SelN(i))
						continue;
					NOTE nn = notes[i];
					nn.midi = -1;
					for (auto c : cb)
					{
						if (FAILED(c->OnNoteChange(this, &notes[i], &nn)))
							return;
					}
					R = true;
					if (!U)
						PushUndo();
					U = true;
					notes.erase(notes.begin() + i);
					i = (size_t)-1;
				}
				if (!R)
					return;
				Redraw();
				return;

			}
		}

		void NormalizePosition(NOTE& n)
		{
			if (n.p.f.n < 0 && n.p.f.d < 0)
			{
				n.p.f.n = -n.p.f.n;
				n.p.f.d = -n.p.f.d;
			}
			if (n.p.f < 0)
			{
				if (n.p.f.n >= 0 && n.p.f.d < 0)
				{
					n.p.f.n = -n.p.f.n;
					n.p.f.d = -n.p.f.d;
				}
				for (;;)
				{
					if (n.p.f.n >= 0)
						break; // duh
					if (n.p.m == 0)
						break; // duh

					auto ti = TimeAtMeasure(n.p.m - 1);
					FRACTION b(ti.nb, DENOM);
					n.p.f += b;
					n.p.m--;
				}
				return;
			}

			for (;;)
			{
				
				auto ti = TimeAtMeasure(n.p.m);
				FRACTION b(ti.nb, DENOM);
				if (n.p.f < b)
					break;
				n.p.f -= b;
				n.p.m++;
			}
		}

		void Quantize(NOTE& n)
		{
			float x = PositionToX(n.p);
			if (x < 0)
				return;
			auto e1 = MeasureAndBarHitTest(x);
			n.p = e1;

			// Position
			auto end = n.EndX();
			float x2 = PositionToX(end);
			if (x2 < 0)
				return;
			auto e2 = MeasureAndBarHitTest(x2);
			if (e1 == e2)
				e2.f.n++;
			auto a1 = AbsF(e1);
			auto a2 = AbsF(e2);
			auto d1 = DistanceBetweenAbs(a2, a1);
			float x42 = PositionToX(e2);
			e2.f.n++;
			auto a3 = AbsF(e2);
			float x43 = PositionToX(e2);
			auto d2 = DistanceBetweenAbs(a3, a1);


			if (fabs(x42 - x2) < fabs(x43 - x2))
				n.d = d1;
			else
				n.d = d2;
		}

		void Paste()
		{
			if (clip.empty() || LastClickN.m == -1)
				return;

			NOTE first = clip[0];
			int di = first.midi - LastClickN.noteht;
			auto a1 = AbsF(first.p);
			auto a2 = AbsF(LastClickN);
			auto dim =  DistanceBetweenAbs(a1, a2);
			PushUndo();

			size_t ep = FindEmptyPart();

			for (auto& n : clip)
			{
				NOTE n2 = n;
				// Note, and position that changes
				n2.midi -= di;
				n2.p.f -= dim;
				NormalizePosition(n2);
				n2.layer = NextLayer;
				if (PartMode)
					n2.part = ep;
				notes.push_back(n2);
			}

			if (PartMode)
				parts[ep].n = L"";
			std::sort(notes.begin(), notes.end());
			Redraw();
		}

		void MouseMove(WPARAM, LPARAM ll)
		{
			bool Shift = ((GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0);
			bool Control = ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0);
			bool LeftClick = ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0);
			int xx = LOWORD(ll);
			int yy = HIWORD(ll);


			if (Tool == TOOL::PAINT && LeftClick)
			{
				if (PartMode)
				{
					auto ip = PartHitTest((float)xx, (float)yy);
					if (ip != -1)
					{
						// Copy this part
						clip.clear();
						for (auto& n : notes)
						{
							if (n.layer != NextLayer)
								continue;
							if (n.part == (size_t)ip)
							{
								clip.push_back(n);
								n.Selected = false;
							}
						}
					}
					else
					{
						// Dup Part
						LastClickN = MeasureAndBarHitTest((FLOAT)xx);
						LastClickN.noteht = MidiHitTest((FLOAT)yy);
						LastClick.x = xx;
						LastClick.y = yy;
						Paste();
					}
				}
				else
				{
					auto ni = NoteAtPos(xx, yy);
					if (ni != -1)
					{
						Deselect(NextLayer, (size_t)-1);
						// Copy this note
						clip.clear();
						clip.push_back(notes[ni]);
						notes[ni].Selected = true;
						Redraw();
						return;
					}
					else
					{
						// Dup Note
						LastClickN = MeasureAndBarHitTest((FLOAT)xx);
						LastClickN.noteht = MidiHitTest((FLOAT)yy);
						LastClick.x = xx;
						LastClick.y = yy;
						Paste();
					}
				}
			}



			if (Tool == TOOL::QUANTIZE && LeftClick)
			{
				// Quantizer
				auto ni = NoteAtPos(xx, yy);
				if (ni != -1)
				{
					if (!Selecting)
						PushUndo();
					Selecting = true;
					Quantize(notes[ni]);
					Redraw();
				}
				return;
			}

			if (Tool == TOOL::ERASER && LeftClick)
			{
				auto ni = NoteAtPos(xx, yy);
				if (ni != -1)
				{
					if (!Selecting)
						PushUndo();
					Selecting = true;
					notes.erase(notes.begin() + ni);
					Redraw();
				}
				return;
			}

			if (Selecting)
			{
				D2D1_RECT_F& d3 = SelectRect;
				d3.left = (FLOAT)LastClick.x;
				
				d3.right = (FLOAT)xx;
				if (xx < LastClick.x)
				{
					d3.right = (FLOAT)LastClick.x;
					d3.left = (FLOAT)xx;
				}

				// Snap
				if (!Shift)
				{
					auto p1 = MeasureAndBarHitTest(d3.left);
					d3.left = PositionToX(p1);
					auto p2 = MeasureAndBarHitTest(d3.right);
					d3.right = PositionToX(p2);

					d3.top = (FLOAT)LastClick.y;
					d3.bottom = (FLOAT)yy;
					if (yy < LastClick.y)
					{
						d3.bottom = (FLOAT)LastClick.y;
						d3.top = (FLOAT)yy;
					}

					// Snap
					size_t pidx1 = (size_t)-1;
					auto n1 = MidiHitTest(d3.top, &pidx1);
					if (n1 >= 0 && pidx1 >= 0)
						d3.top = DrawedNotes[pidx1].full.top;
					size_t pidx2 = (size_t)-1;
					auto n2 = MidiHitTest(d3.bottom, &pidx2);
					if (n2 >= 0 && pidx2 >= 0)
						d3.bottom = DrawedNotes[pidx2].full.bottom;
				}

				for (auto& n : notes)
				{
					if (n.layer != NextLayer)
						continue;
					if (InRect(SelectRect, n.dr.right + 1, n.dr.bottom + 1))
						n.Selected = true;
					else
						if (InRect(SelectRect, (FLOAT)n.dr.left + 1, (FLOAT)n.dr.top + 1))
							n.Selected = true;
						else
						{
							if (!Shift)
								n.Selected = false;
						}
				}

				SetCursor(CursorSelect);
				Redraw();
				return;
			}
			if (BarMoving)
			{
				int nx = LOWORD(ll);
				int pts = nx - LastClick.x;
				// Convert these to Viewing
				// In TopBar full, FullNotesWidth
				// In This		,  ?
				if (pts >= 0)
					ScrollX += TotalWidthForMusic * pts / (top.full.right - top.full.left);
				else
					ScrollX -= TotalWidthForMusic * -pts / (top.full.right - top.full.left);
				if (ScrollX < 0)
					ScrollX = 0;
				LastClick.x = nx;
				Redraw(0);
			}
			// Side
			if (PianoClicking)
			{
				// Find the note, back search
				for (int y = (int)DrawnPiano.size() - 1; y >= 0; y--)
				{
					auto& pd = DrawnPiano[y];
					if (InRect(pd.full, LOWORD(ll), HIWORD(ll)))
					{
						if (PianoNoteClicked != pd.m)
						{
							if (PianoNoteClicked != -1)
							{
								for (auto c : cb)
									c->OnPianoOff(this, PianoNoteClicked, DefPianoChannel);
							}
							PianoNoteClicked = pd.m;
							if (PianoNoteClicked != -1)
							{
								for (auto c : cb)
									c->OnPianoOn(this, PianoNoteClicked,DefPianoVelocity,DefPianoChannel);
							}

							Redraw(2);
						}
						break;
					}
				}
				return;
			}


			if (PartMode && GroupDragging)
			{
//				for(auto& )
				// Assume Note is at center
				// Drag this note, then drag all the rest of thte group relatively
				auto hp = MeasureAndBarHitTest((float)xx, Shift);
				NOTE nx = *GroupDragging;
				nx.p.m = hp.m;
				nx.p.f = hp.f;
				int np = MidiHitTest((float)yy);
				nx.midi = np;
				NOTE oldn = *GroupDragging;
				*GroupDragging = nx;

				// Comparing now GroupDragging and oldn, move all group
				int mididiff = oldn.midi - GroupDragging->midi;
				auto a1 = AbsF(oldn.p);
				auto a2 = AbsF(GroupDragging->p);
				auto npx = DistanceBetweenAbs(a1,a2);
				for (auto& n : notes)
				{
					if (n.layer != NextLayer)
						continue;
					if (n.part != oldn.part)
						continue;

					n.midi -= mididiff;
					n.p.f -= npx;
				}

				Redraw();
			}

			if (NoteDragging)
			{
				auto hp = MeasureAndBarHitTest((float)xx,Shift);
				NOTE nx = *NoteDragging;
				nx.p.m = hp.m;
				nx.p.f = hp.f;

				int np = MidiHitTest((float)yy);
				nx.midi = np;
				for (auto c : cb)
				{
					if (FAILED(c->OnNoteChange(this, NoteDragging, &nx)))
						return;
				}
				*NoteDragging = nx;
				Redraw();
			}

			if (NoteResizing)
			{
				SetCursor(CursorResize);
#ifdef _DEBUG
				///	if (Shift) DebugBreak();
#endif

				auto hp = MeasureAndBarHitTest((float)xx, Shift);
				if (hp.m == -1)
					return;
				if (ResizingRight)
				{
#ifdef _DEBUG
					if (Control) DebugBreak();
#endif
					// Enlarge note
					if (!Shift)
						hp.f.n++; // Add a beat
					if (hp.m < NoteResizing->p.m)
						return; // Back Measure
					if (hp.m == NoteResizing->p.m && hp.f < NoteResizing->p.f)
						return; // Back Inside
					NOTE nn = *NoteResizing;
					auto a1 = AbsF(hp);
					auto a2 = AbsF(NoteResizing->p);
					nn.d = DistanceBetweenAbs(a1, a2);
#ifdef _DEBUG
//					auto nd = a1.ToFraction() - a2.ToFraction();
//					nd.d *= DENOM;
//					wchar_t a[100];		swprintf_s(a, 100, L"New %u + %u/%u (dur %u/%u), Old %u + %u/%u (dur %u/%u) \r\n",a1.beats, a1.f.n, a1.f.d, nd.n,nd.d,a2.beats,a2.f.n, a2.f.d,NoteResizing->d.n, NoteResizing->d.d);	OutputDebugString(a);
#endif
					if (nn.d.n <= 0)
						return;
					for (auto c : cb)
					{
						if (FAILED(c->OnNoteChange(this, NoteResizing, &nn)))
							return;
					}
					nn.d.simplify();
					*NoteResizing = nn;
					Redraw();
				}
				else
				{
					// Change Position
					auto nend = NoteResizing->EndX();
					auto maxp = AbsF(nend);
					auto newp = AbsF(hp);
					if (newp >= maxp)
						return;
					NOTE nn = *NoteResizing;
					nn.d = DistanceBetweenAbs(maxp,newp);
					nn.p = hp;
					for (auto c : cb)
					{
						if (FAILED(c->OnNoteChange(this, NoteResizing, &nn)))
							return;
					}
					NoteResizing->p = hp;
					NoteResizing->d = nn.d.simplify();
					Redraw();
				}


				return;
			}

			// Cursor pos for resizing
			auto ni = NoteAtPos(xx, yy, true);
			if (ni != -1 && !NoteDragging)
			{
				SetCursor(CursorResize);
			}
			else
			if (Selecting && Tool == TOOL::AUTO)
				SetCursor(CursorSelect);
			else
			if (Tool == TOOL::ERASER)
				SetCursor(CursorErase);
			else
			if (Tool == TOOL::QUANTIZE)
				SetCursor(CursorResize4);
			else
			if (Tool == TOOL::SINGLE)
				SetCursor(CursorHand);
			else
				SetCursor(CursorArrow);

			if (ViewLiveNotes == 1 && !LeftClick)
			{
				ssize_t nit = NoteAtPos(xx, yy);
				if (nit == -1)
				{
					size_t lidx = 0;
					size_t didx = 0;
					auto n1 = MidiHitTest((float)yy, &lidx);
					auto hp = MeasureAndBarHitTest((float)xx, 0, &didx);
					if (LastNoteOver != n1 || hp.m != LastOverHP.m || hp.f != LastOverHP.f)
					{
						LastNoteOver = n1;
						LastOverHP = hp;
						LastNoteOverIdx = lidx;
						LastBeatOverIdx = didx;
						Redraw();
					}
				}
				else
				{
					if (LastNoteOverIdx != -1)
					{
						LastNoteOverIdx = (size_t)-1;
						LastBeatOverIdx = (size_t)-1;
						Redraw();
					}
				}
			}


		}

		void LeftUp(WPARAM, LPARAM)
		{
			if (PianoNoteClicked != -1)
			{
				for (auto c : cb)
					c->OnPianoOff(this, PianoNoteClicked, DefPianoChannel);
			}
			if (NoteResizing || NoteDragging)
				std::sort(notes.begin(), notes.end());
			NoteResizing = 0;
			GroupDragging = 0;
			NoteDragging = 0;
			Selecting = false;
			SelectRect.left = SelectRect.top = SelectRect.right = SelectRect.bottom = 0;
			PianoNoteClicked = -1;
			PianoClicking = false;
			BarMoving = false;
			Redraw();
		}

		void RightDown(WPARAM, LPARAM ll,int ForceSelected = 0,int ForceNotSelected = 0)
		{
			auto hp = MeasureAndBarHitTest(LOWORD(ll));
			LastClick.x = LOWORD(ll);
			LastClick.y = HIWORD(ll);

			if (!ForceSelected && !ForceNotSelected && InRect(side.full, LastClick.x, LastClick.y))
			{
				PianoRight();
				return;
			}
			// Selected ?
			bool S = false;
			bool Need = false;
			auto ni = NoteAtPos(LOWORD(ll), HIWORD(ll));
			if (ForceNotSelected)
				ni = -1;
			if (ni != -1)
			{
				if (notes[ni].Selected == false)
					Need = true;
				notes[ni].Selected = true;
				S = true;
			}
			else
			{
				// Other selected?
				for (auto& n : notes)
				{
					if (n.Selected)
					{
						S = true;
						break;
					}
				}
			}

			if (ForceNotSelected)
				S = false;

			if (S)
			{
				// Selected menu
				auto m = CreatePopupMenu();
				AppendMenu(m, MF_STRING, 1, L"Delete\tDel");
				AppendMenu(m, MF_SEPARATOR, 0, L"");
				AppendMenu(m, MF_STRING, 3, L"Move Down\t-");
				AppendMenu(m, MF_STRING, 2, L"Move Up\t+");
				AppendMenu(m, MF_SEPARATOR, 0, L"");
				AppendMenu(m, MF_STRING, 67, L"Chromatically Move Down\tShift -");
				AppendMenu(m, MF_STRING, 68, L"Chromatically Move Up\tShift +");
				AppendMenu(m, MF_SEPARATOR, 0, L"");
				AppendMenu(m, MF_STRING, 11, L"Velocity Down\t<");
				AppendMenu(m, MF_STRING, 12, L"Velocity Up\t>");
				AppendMenu(m, MF_STRING, 21, L"Velocity...");
				AppendMenu(m, MF_SEPARATOR, 0, L"");
				AppendMenu(m, MF_STRING, 15, L"Channel Down\tShift+Down");
				AppendMenu(m, MF_STRING, 16, L"Channel Up\tShift+Up");
				AppendMenu(m, MF_SEPARATOR, 0, L"");
				AppendMenu(m, MF_STRING, 17, L"Layer Down\tAlt+Down");
				AppendMenu(m, MF_STRING, 18, L"Layer Up\tAlt+Up");
				AppendMenu(m, MF_SEPARATOR, 0, L"");
				AppendMenu(m, MF_STRING, 13, L"Expand\t/");
				AppendMenu(m, MF_STRING, 14, L"Reduce\t\\");
				AppendMenu(m, MF_STRING, 76, L"Move right\tX");
				AppendMenu(m, MF_STRING, 77, L"Move left\tZ");
				AppendMenu(m, MF_STRING, 71, L"Double\tD");
				AppendMenu(m, MF_STRING, 72, L"Half\tH");
				AppendMenu(m, MF_STRING, 73, L"+1/2\t'");
				AppendMenu(m, MF_SEPARATOR, 0, L"");
				AppendMenu(m, MF_STRING, 66, L"Quantize\tCtrl+Q");
				AppendMenu(m, MF_STRING, 74, L"Diatonic Transpose\tCtrl+T");
				AppendMenu(m, MF_STRING, 75, L"Chromatic Transpose\tCtrl+Shift+T");
				POINT p;
				GetCursorPos(&p);
				int tcmd = ForceSelected;
				if (tcmd == 0)
					tcmd = TrackPopupMenu(m, TPM_CENTERALIGN | TPM_RETURNCMD, p.x, p.y, 0, hParent, 0);
				DestroyMenu(m);
				if (tcmd == 1)
				{
					KeyDown(VK_DELETE, 0);
				}
				if (tcmd == 2)
				{
					KeyDown(VK_ADD, 0);
				}
				if (tcmd == 3)
				{
					KeyDown(VK_SUBTRACT, 0);
				}
				if (tcmd == 68)
				{
					KeyDown(VK_ADD, 0,true);
				}
				if (tcmd == 67)
				{
					KeyDown(VK_SUBTRACT, 0, true);
				}
				if (tcmd == 11)
				{
					KeyDown(188, 0);
				}
				if (tcmd == 12)
				{
					KeyDown(190, 0);
				}
				if (tcmd == 13)
				{
					KeyDown(191, 0);
				}
				if (tcmd == 14)
				{
					KeyDown(220, 0);
				}
				if (tcmd == 66)
				{
					KeyDown('Q', 0,0,true);
				}
				if (tcmd == 74)
				{
					KeyDown('T', 0, 0, true);
				}
				if (tcmd == 75)
				{
					KeyDown('T', 0, true, true);
				}
				if (tcmd == 71)
				{
					KeyDown('D', 0);
				}
				if (tcmd == 72)
				{
					KeyDown('H', 0);
				}
				if (tcmd == 77)
				{
					KeyDown('Z', 0);
				}
				if (tcmd == 76)
				{
					KeyDown('X', 0);
				}
				if (tcmd == 73)
				{
					KeyDown(222, 0);
				}
				if (tcmd == 15)
				{
					KeyDown(VK_DOWN, 0,true);
				}
				if (tcmd == 16)
				{
					KeyDown(VK_UP, 0, true);
				}
				if (tcmd == 17)
				{
					KeyDown(VK_DOWN, 0, 0,0,true);
				}
				if (tcmd == 18)
				{
					KeyDown(VK_UP, 0, 0,0,true);
				}
				if (tcmd == 21)
				{
					// Velocity entry
					vector<wchar_t> re(1000);
					if (!AskText(hParent, L"Velocity", L"Enter velocity (0-127):", re.data()))
						return;

					int vel = _wtoi(re.data());
					if (vel < 0 || vel > 127)
						vel = 127;

					bool R = false, U = false;
					for (auto& n : notes)
					{
						if (n.layer != NextLayer)
							continue;
						if (n.Selected || n.PartSelected(parts))
						{
							NOTE nn = n;
							nn.vel  = vel;
							if (nn.nonote > 0 && ((nn.nonote & 0xF0) == 0xA0))
							{
								nn.nonote &= 0xFFFF;
								nn.nonote |= (nn.vel << 16);
							}
							for (auto c : cb)
							{
								if (FAILED(c->OnNoteChange(this, &n, &nn)))
									return;
							}
							if (!U)
								PushUndo();
							U = true;
							R = true;
							n.vel = nn.vel;
						}
					}
					if (R)
						Redraw();
				}
			}
			else
			{
				// Not Selected menu
				KEY k = KeyAtMeasure(hp.m);
				TEMPO tx = TempoAtMeasure(hp.m);
				auto m = CreatePopupMenu();
				wchar_t re[1000] = { 0 };

				auto m0 = CreatePopupMenu();
				AppendMenu(m0, MF_STRING, 51, L"Auto\tA");
				AppendMenu(m0, MF_STRING, 52, L"Eraser\tE");
				AppendMenu(m0, MF_STRING, 53, L"Single Click Entry\tI");
				AppendMenu(m0, MF_STRING, 54, L"Quantizer\tQ");
				AppendMenu(m0, MF_STRING, 55, L"Paint\tN");
				AppendMenu(m, MF_POPUP | MF_STRING, (UINT_PTR)m0, L"Tool");
				AppendMenu(m, MF_SEPARATOR, 0, L"");


				if (true)
				{
					auto m1 = CreatePopupMenu();
					swprintf_s(re, L"Key Set (Current: %i)\t", k.k);
					AppendMenu(m1, MF_STRING, 1, re);
					AppendMenu(m1, MF_STRING, 2, L"Mode Major");
					AppendMenu(m1, MF_STRING, 3, L"Mode Minor");
					AppendMenu(m1, MF_SEPARATOR, 0, L"");
					swprintf_s(re, L"Tempo Set (Current: %i)\t", tx.BpM);
					AppendMenu(m1, MF_STRING, 64, re);
					AppendMenu(m1, MF_SEPARATOR, 0, L"");
					swprintf_s(re, L"Beats\t");
					AppendMenu(m1, MF_STRING, 4, re);

					AppendMenu(m, MF_POPUP | MF_STRING, (UINT_PTR)m1, L"This measure on");
					AppendMenu(m, MF_SEPARATOR, 0, L"");
				}

				if (true) 
				{
					auto mx = CreatePopupMenu();
					AppendMenu(mx, MF_STRING, 111, L"Left");
					AppendMenu(mx, MF_STRING, 112, L"Right");
					AppendMenu(m, MF_POPUP | MF_STRING, (UINT_PTR)mx, L"Direction");
					AppendMenu(m, MF_SEPARATOR, 0, L"");
				}
				if (true)
				{
					auto mx = CreatePopupMenu();
					AppendMenu(mx, MF_STRING, 113, L"Side");
					AppendMenu(mx, MF_STRING, 114, L"Bottom");
					AppendMenu(mx, MF_STRING, 115, L"Off");
					AppendMenu(m, MF_POPUP | MF_STRING, (UINT_PTR)mx, L"Piano");
					AppendMenu(m, MF_SEPARATOR, 0, L"");
				}

				if (true)
				{
					auto mx = CreatePopupMenu();
					AppendMenu(mx, MF_STRING, 121, L"Velocities");
					AppendMenu(mx, MF_STRING, 122, L"Channels");
					AppendMenu(mx, MF_STRING, 123, L"Layers");
					AppendMenu(mx, MF_STRING, 125, L"Live Notes");
					AppendMenu(mx, MF_SEPARATOR, 0, L"");
					AppendMenu(mx, MF_STRING, 124, L"Go to measure...\tCtrl+G");
					AppendMenu(m, MF_POPUP | MF_STRING, (UINT_PTR)mx, L"View");
					AppendMenu(m, MF_SEPARATOR, 0, L"");
				}

				auto m2 = CreatePopupMenu();
				swprintf_s(re, L"Set next (Current: %i)\t", NextLayer + 1);
				AppendMenu(m2, MF_STRING, 6,re);
				swprintf_s(re, L"Next Layer (Use keypad 1-9)\t");
				AppendMenu(m2, MF_STRING, 0, re);
				swprintf_s(re, L"Show/Hide Layer (Use Alt+keypad 1-9)\t");
				AppendMenu(m2, MF_STRING, 0, re);
				AppendMenu(m, MF_POPUP | MF_STRING, (UINT_PTR)m2, L"Layer");
				AppendMenu(m, MF_SEPARATOR, 0, L"");

				if (true)
				{
					auto mx = CreatePopupMenu();
					AppendMenu(mx, MF_STRING, 151, L"Toggle part mode\tP");
					swprintf_s(re, L"Set next (Current: %i)\tAlt+P", NextPart + 1);
					AppendMenu(mx, MF_STRING, 152, re);
					AppendMenu(mx, MF_STRING, 153, L"Selected part name\tShift+P");
					AppendMenu(m, MF_POPUP | MF_STRING, (UINT_PTR)mx, L"Part");
					AppendMenu(m, MF_SEPARATOR, 0, L"");

				}



				auto m3 = CreatePopupMenu();
				swprintf_s(re, L"Resolution /1\tCtrl+1");
				AppendMenu(m3, MF_STRING, 21, re);
				swprintf_s(re, L"Resolution /2\tCtrl+2");
				AppendMenu(m3, MF_STRING, 22, re);
				swprintf_s(re, L"Resolution /3\tCtrl+3");
				AppendMenu(m3, MF_STRING, 23, re);
				swprintf_s(re, L"Resolution /4\tCtrl+4");
				AppendMenu(m3, MF_STRING, 24, re);
				swprintf_s(re, L"Resolution /5\tCtrl+5");
				AppendMenu(m3, MF_STRING, 25, re);
				swprintf_s(re, L"Resolution /6\tCtrl+6");
				AppendMenu(m3, MF_STRING, 26, re);
				AppendMenu(m, MF_POPUP | MF_STRING, (UINT_PTR)m3, L"Snap");
				AppendMenu(m, MF_SEPARATOR, 0, L"");


				auto m4 = CreatePopupMenu();
				swprintf_s(re, L"1 Beat\t1");
				AppendMenu(m4, MF_STRING, 31, re);
				swprintf_s(re, L"2 Beats\t2");
				AppendMenu(m4, MF_STRING, 32, re);
				swprintf_s(re, L"3 Beats\t3");
				AppendMenu(m4, MF_STRING, 33, re);
				swprintf_s(re, L"4 Beats\t4");
				AppendMenu(m4, MF_STRING, 34, re);
				swprintf_s(re, L"1/2 Beat\tShift+2");
				AppendMenu(m4, MF_STRING, 42, re);
				swprintf_s(re, L"1/3 Beat\tShift+3");
				AppendMenu(m4, MF_STRING, 43, re);
				swprintf_s(re, L"1/4 Beat\tShift+4");
				AppendMenu(m4, MF_STRING, 44, re);
				AppendMenu(m, MF_POPUP | MF_STRING, (UINT_PTR)m4, L"Next Note size");
				AppendMenu(m, MF_SEPARATOR, 0, L"");
				

				if (true)
				{
					auto mx = CreatePopupMenu();
					auto mins = midiInGetNumDevs();
					AppendMenu(mx, MF_STRING, 2000, L"None");
					for (size_t i = 0; i < mins; i++)
					{
						if (i == 0)
							AppendMenu(mx, MF_SEPARATOR, 0, L"");
						MIDIINCAPS2 m22 = { 0 };
						midiInGetDevCaps(i, (MIDIINCAPS*)&m22, sizeof(m22));
						AppendMenu(mx, MF_STRING, 2001 + i, m22.szPname);
					}
					AppendMenu(m, MF_POPUP | MF_STRING, (UINT_PTR)mx, L"MIDI in recording");
				}
//				AppendMenu(m, MF_SEPARATOR, 0, L"");
//				AppendMenu(m, MF_STRING, 999, L"Special selection...");

				POINT p;
				GetCursorPos(&p);
				int tcmd = ForceNotSelected;
				if (tcmd == 0)
					tcmd = TrackPopupMenu(m, TPM_CENTERALIGN | TPM_RETURNCMD, p.x, p.y, 0, hParent, 0);
				DestroyMenu(m);
/*				if (tcmd ==  999)
					{
					SpecialSelectionDP(hParent);
					}
*/				if (tcmd == 1)
				{
					swprintf_s(re, L"%i", k.k);
					if (!AskText(hParent, L"Key", L"Enter key:", re))
						return;
					KEY k2 = k;
					k2.k = _wtoi(re);
					if (k2.k < -7 || k.k > 7)
						k2.k = 0;
					k2.CreateScale();
					k2.atm = hp.m;
					Keys.push_back(k2);
					sort(Keys.begin(), Keys.end());
					Redraw();
				}
				if (tcmd == 2 || tcmd == 3)
				{
					KEY k2 = k;
					k2.m = (tcmd == 2) ? 0 : 1;
					k2.CreateScale();
					Keys.push_back(k2);
					sort(Keys.begin(), Keys.end());
					Redraw();
				}
				if (tcmd == 151)
				{
					KeyDown('P');
					return;
				}
				if (tcmd == 152)
				{
					KeyDown('P',0,0,0,true);
					return;
				}
				if (tcmd == 153)
				{
					KeyDown('P', 0, true, 0);
					return;
				}

				if (tcmd == 64)
				{
					swprintf_s(re, L"%i", tx.BpM);
					if (!AskText(hParent, L"Tempo", L"Enter tempo:", re))
						return;
					TEMPO k2 = tx;
					k2.BpM = _wtoi(re);
					if (k2.BpM < 0)
						k2.BpM = 120;
					k2.atm = hp.m;
					Tempos.push_back(k2);
					sort(Tempos.begin(), Tempos.end());
					Redraw();
				}
				if (tcmd == 4)
				{
					swprintf_s(re, L"");
					if (!AskText(hParent, L"Beats", L"Enter beats:", re))
						return;
					int nb = _wtoi(re);
					if (!nb)
						return;

					TIME t;
					t.nb = nb;
					t.atm = hp.m;
					Times.push_back(t);
					std::sort(Times.begin(), Times.end());
					Redraw();
				}
				if (tcmd == 6)
				{
					swprintf_s(re, L"%i", NextLayer + 1);
					if (!AskText(hParent, L"Layer", L"Enter layer (You can also use the keypad 1-9 to select the layer, and alt+keypad to toggle layer visibility):", re))
						return;
					NextLayer = _wtoi(re) - 1;
					if (NextLayer < 0)
						NextLayer = 0;
					return;
				}

				if (tcmd >= 21 && tcmd <= 26)
				{
					snapres = tcmd - 20;
					Redraw();
				}
				if (tcmd == 31) noteres = -1;
				if (tcmd == 32) noteres = -2;
				if (tcmd == 33) noteres = -3;
				if (tcmd == 34) noteres = -4;

				if (tcmd == 42) noteres = 2;
				if (tcmd == 43) noteres = 3;
				if (tcmd == 44) noteres = 4;

				if (tcmd >= 51 && tcmd <= 55)
				{
					Tool = (TOOL)(tcmd - 51);
					Redraw();
				}

				if (tcmd == 111)
				{
					Direction = 0;
					Redraw();
				}
				if (tcmd == 112)
				{
					Direction = 1;
					Redraw();
				}
				if (tcmd == 113)
				{
					PianoPosition = 0;
					side.Width = 150;
					Redraw();
				}
				if (tcmd == 114)
				{
					PianoPosition = 1;
					side.Width = 150;
					Redraw();
				}
				if (tcmd == 115)
				{
					PianoPosition = 0;
					side.Width = 0;
					Redraw();
				}

				if (tcmd == 121)
				{
					ViewVelocity = !ViewVelocity;
					Redraw();
				}
				if (tcmd == 122)
				{
					ViewChannels = !ViewChannels;
					Redraw();
				}
				if (tcmd == 123)
				{
					ViewLayers = !ViewLayers;
					Redraw();
				}
				if (tcmd == 124)
				{
					KeyDown('G', 0,0,true);
				}

				if (tcmd == 121)
				{
					ViewLiveNotes = !ViewLiveNotes;
					Redraw();
				}

				if (tcmd >= 2000)
				{
					min.Close();
					// Midi-In opening
					if (tcmd > 2000)
					{
						min.mid = tcmd - 2001;
						midiInOpen(&min.m, min.mid, (DWORD_PTR)PIANOROLL::MidiInProc, (DWORD_PTR)this, CALLBACK_FUNCTION);
						midiInStart(min.m);
					}
				}
			}


			if (Need)
				Redraw();
		}

		bool Deselect(ssize_t atl,size_t exc)
		{
			bool Need = false;
			for (size_t i = 0; i < notes.size(); i++)
			{
				auto& n = notes[i];
				if (atl != -1 && n.layer != atl)
					continue;
				if (i == exc)
					continue;
				if (n.Selected)
				{
					Need = true;
					n.Selected = false;
					for (auto c : cb)
						c->OnNoteSelect(this, &n, 0);
				}
			}

			return Need;
		}

		void LeftDown(WPARAM ww, LPARAM ll)
		{
			bool Shift = ((GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0);
			Selecting = false;
			int xx = LOWORD(ll);
			int yy = HIWORD(ll);
			LastClickN = MeasureAndBarHitTest((FLOAT)xx);
			MidiInInsert = LastClickN;
			LastClickN.noteht = MidiHitTest((FLOAT)yy);
			LastClick.x = xx;
			LastClick.y = yy;
			
			// Bar
			if (InRect(top.full, xx, yy))
			{
				BarMoving = true;
				return;
			}

			// Info
			if (InRect(info.full, xx, yy))
			{
				//*
				return;
			}

			// Side
			if (InRect(side.full, LOWORD(ll), HIWORD(ll)))
			{
				PianoClicking = true;

				// Find the note, back search
				for (int y = (int)DrawnPiano.size() - 1; y >= 0; y--)
				{
					auto& pd = DrawnPiano[y];
					if (InRect(pd.full, LOWORD(ll), HIWORD(ll)))
					{
						if (PianoNoteClicked != -1)
						{
							for (auto c : cb)
								c->OnPianoOff(this, PianoNoteClicked, DefPianoChannel);
						}
						PianoNoteClicked = pd.m;
						if (PianoNoteClicked != -1)
						{
							for (auto c : cb)
								c->OnPianoOn(this, PianoNoteClicked,DefPianoVelocity,DefPianoChannel);
						}
						break;
					}
				}

				Redraw(2);
				return;
			}

			// Find note there
			bool Need = false;
			auto ni = NoteAtPos(xx, yy);


			if (Tool == TOOL::ERASER || Tool == TOOL::QUANTIZE || Tool == TOOL::PAINT)
			{
				MouseMove(ww, ll);
				return;
			}


			auto ni2 = NoteAtPos(xx, yy, true, &ResizingRight);

			if (ni2 != -1)
			{
				NoteResizing = &notes[ni2];
				NoteResizingSt = *NoteResizing;
				SetCursor(CursorResize);
				return;
			}

			if (ni == -1 && Tool == TOOL::SINGLE)
			{
				LeftDoubleClick(ww, ll);
				return;
			}

			// Part
			if (ni == -1 && PartMode && Tool != TOOL::SINGLE)
			{
				bool U = false;
				if (!Shift)
				{
					for (auto& p : parts)
					{
						if (p.second.S)
						{
							p.second.S = false;
/*							for (auto& nn : notes)
							{
								if (nn.layer == NextLayer && nn.part == p.first)
									nn.Selected = false;
							}
*/							U = true;
						}
					}
				}

				auto ip = PartHitTest((float)xx, (float)yy);
				if (ip != -1)
				{
					parts[ip].S = true;
					GroupDragging = make_shared<NOTE>();
					GroupDragging->part = ip;
					auto hp = MeasureAndBarHitTest((float)xx, Shift);
					GroupDragging->p.m = hp.m;
					GroupDragging->p.f = hp.f;

					int np = MidiHitTest((float)yy);
					GroupDragging->midi = np;

					/*					for (auto& nn : notes)
					{
						if (nn.layer == NextLayer && nn.part == (size_t)ip)
							nn.Selected = true;
					}
*/					U = true;
				}
				if (U)
				{
					Redraw();
					if (ip != -1)
						return;
				}
			}

			// Deselect
			if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) == 0)
			{
				Need = Deselect(NextLayer,ni);
			}
			if (ni != -1)
			{
				notes[ni].Selected = !notes[ni].Selected;
				Need = true;
				NoteDragging = &notes[ni];
				for (auto c : cb)
					c->OnNoteSelect(this, &notes[ni], notes[ni].Selected);
			}
			else
			{
				Selecting = true;
			}
			if (Need)
			{
				Redraw();
			}
		}

		void LeftDoubleClick(WPARAM, LPARAM ll,tuple<POSITION,int,NOTE*>* fromMidi = 0)
		{
			if (!fromMidi)
			{
				if (Tool == TOOL::ERASER || Tool == TOOL::QUANTIZE)
					return;
			}
			int xx = LOWORD(ll);
			int yy = HIWORD(ll);

			if (InRect(side.full, xx, yy))
			{
				return;
			}

			bool Shift = ((GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0);
			bool Control = ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0);
			//			bool Alt = ((GetAsyncKeyState(VK_MENU) & 0x8000) != 0);

			bool U = false;
			// Find note there
			auto ni = NoteAtPos(LOWORD(ll), HIWORD(ll));
			if (fromMidi)
				ni = (size_t)-1;
			if (ni != -1)
			{
				for (auto c : cb)
				{
					if (FAILED(c->NoteRemoved(this, &notes[ni])))
						return;
				}
				if (!U)
					PushUndo();
				U = true;
				notes.erase(notes.begin() + ni);
				Redraw();
				return;
			}

			// Next LAyer hidden?
			auto nextl = std::lower_bound(HiddenLayers.begin(), HiddenLayers.end(), NextLayer);
			if (nextl != HiddenLayers.end() && *nextl == NextLayer)
				return;

			auto e1 = fromMidi ? get<0>(*fromMidi) : MeasureAndBarHitTest(LOWORD(ll));
			auto e2 = fromMidi ? get<1>(*fromMidi) : MidiHitTest(HIWORD(ll));
			if (e1.m != -1 && e2 > 0)
			{
				auto msr = DrawnMeasureByIndex(e1.m);
				if (!msr)
					return;
				// Insert note
				NOTE nx;

				if (Control && Shift)
				{
					nx.vel = 127;
				}

				bool LongEvent = false;
				if (Control && !Shift)
				{
					vector<wchar_t> re(1000);

					HMENU m = CreatePopupMenu();
					if (true) // 16*128 items of patching
					{
						int yd = 1;
						// Channels and patches
						auto m1 = CreatePopupMenu();
						for (int i = 0; i < 15; i++)
						{
							auto m2 = CreatePopupMenu();
							for (int y = 0; y < 128; y++)
							{
								swprintf_s(re.data(), 1000, L"%u.%s", y,gmpa[y]);
								AppendMenu(m2, MF_STRING | ((y % 32) == 0 && y > 0 ? MF_MENUBARBREAK : 0), yd++, re.data());
							}
							swprintf_s(re.data(), 1000, L"Channel %u", i + 1);
							AppendMenu(m1, MF_STRING | MF_POPUP, (UINT_PTR)m2, re.data());
						}
						AppendMenu(m, MF_STRING | MF_POPUP, (UINT_PTR)m1, L"Channel Program");
					}
					if (true) // 16 items of pitch shift
					{
						// Channels and patches
						auto m1 = CreatePopupMenu();
						for (int i = 0; i < 15; i++)
						{
							swprintf_s(re.data(), 1000, L"Channel %u", i + 1);
							AppendMenu(m1, MF_STRING, 2100 + i, re.data());
						}
						AppendMenu(m, MF_STRING | MF_POPUP, (UINT_PTR)m1, L"Pitch Shift");
					}
					AppendMenu(m, MF_SEPARATOR, 0,0);
					AppendMenu(m, MF_STRING | MF_POPUP, 4001, L"Text (FF 01)...");
					AppendMenu(m, MF_STRING | MF_POPUP, 4002, L"Copyright (FF 02)...");
					AppendMenu(m, MF_STRING | MF_POPUP, 4003, L"Track Name (FF 03)...");
					AppendMenu(m, MF_STRING | MF_POPUP, 4004, L"Instrument (FF 04)...");
					AppendMenu(m, MF_STRING | MF_POPUP, 4005, L"Lyric (FF 05)...");
					AppendMenu(m, MF_STRING | MF_POPUP, 4006, L"Marker (FF 06)...\tIns");
					AppendMenu(m, MF_STRING | MF_POPUP, 4007, L"Cue point (FF 07)...");
					AppendMenu(m, MF_STRING | MF_POPUP, 3002, L"Aftertouch");
					AppendMenu(m, MF_STRING | MF_POPUP, 3001, L"Raw Hex code...");
					POINT p;
					GetCursorPos(&p);
					int tcmd = TrackPopupMenu(m, TPM_CENTERALIGN | TPM_RETURNCMD, p.x, p.y, 0, hParent, 0);
					DestroyMenu(m);
					if (tcmd == 0)
						return;
					if (tcmd <= 2048)
					{
						tcmd--;
						int ch = tcmd / 128;
						int yp = tcmd % 128;
						swprintf_s(re.data(), 1000, L"0x00%02XC%X",yp,ch);
						std::wstringstream ss;
						ss << std::hex << re.data();
						ss >> nx.nonote;
						LongEvent = true;
					}
					else
					if (tcmd >= 2100 && tcmd <= 2116)
					{
						nx.nonote = 0x4000E0;
						nx.nonote |= tcmd - 2100;
						LongEvent = true;
					}
					else
					if (tcmd == 3001)
					{
						swprintf_s(re.data(), 1000, L"0x000000");
						if (!AskText(hParent, L"Hex Code", L"Enter hex code for event:", re.data()))
							return;
						std::wstringstream ss;
						ss << std::hex << re.data();
						ss >> nx.nonote;
						LongEvent = true;
					}
					else
					if (tcmd == 3002)
					{
						nx.nonote = 0x7F00A0;
						nx.nonote |= NextChannel;
						nx.nonote |= (e2 << 8);
					}
					else
					if (tcmd >= 4001 && tcmd <= 4007)
					{
						if (tcmd == 4006)
						{
							KeyDown(VK_INSERT);
							return;
						}
						swprintf_s(re.data(), 1000, L"");
						if (!AskText(hParent, L"Text", L"Enter text:", re.data()))
							return;
						LongEvent = true;
						nx.HasMetaEvent = true;
						nx.MetaEvent = (unsigned char)(tcmd - 4000);
						nx.MetaEventData.resize(wcslen(re.data()) * 2);
						memcpy(nx.MetaEventData.data(), re.data(), wcslen(re.data()) * 2);
					}

				}
				nx.midi = e2;
				nx.p.m = e1.m;
				nx.p.f = e1.f;
				if (noteres < 0)
				{
					nx.d.n = abs(noteres);
					nx.d.d = DENOM;
				}
				else
				{
					nx.d.n = 1;
					if (noteres == 1)
						nx.d.d = DENOM * 1;
					if (noteres == 2)
						nx.d.d = DENOM * 2;
					if (noteres == 3)
						nx.d.d = DENOM * 3;
					if (noteres == 4)
						nx.d.d = DENOM * 4;

				}
				if (LongEvent)
					nx.d.n = 4;

				for (auto c : cb)
				{
					if (FAILED(c->NoteAdded(this, &nx)))
						return;
				}
				if (!U)
					PushUndo();
				U = true;
				nx.ch = NextChannel;
				nx.layer = NextLayer;
				nx.part = NextPart;

				if (Control && Shift)
				{
					nx.nonote = 0x0000A0;
					nx.nonote |= nx.ch;
					nx.nonote |= (nx.vel << 16);
					nx.nonote |= (nx.midi << 8);
				}

				notes.push_back(nx);
				if (fromMidi)
					*get<2>(*fromMidi) = nx;
				std::sort(notes.begin(), notes.end());
				Redraw();
			}
		}


		void Message(UINT mm, WPARAM ww, LPARAM ll)
		{
			switch (mm)
			{
				case WM_KEYDOWN:
				case WM_SYSKEYDOWN:
				{
					KeyDown(ww, ll);
					break;
				}
				case WM_MOUSEMOVE:
				{
					MouseMove(ww, ll);
					break;
				}
				case WM_LBUTTONDOWN:
				{
					LeftDown(ww, ll);
					break;
				}
				case WM_LBUTTONUP:
				{
					LeftUp(ww, ll);
					break;
				}
				case WM_LBUTTONDBLCLK:
				{
					LeftDoubleClick(ww, ll);
					break;
				}
				case WM_RBUTTONDOWN:
				{
					RightDown(ww, ll);
					break;
				}
			}
		}

		void PianoRight()
		{
			POINT p;
			GetCursorPos(&p);

			auto m = CreatePopupMenu();
			AppendMenu(m, MF_STRING, 11, L"Velocity...");
			AppendMenu(m, MF_STRING, 13, L"Channel...");
			if (PianoPosition == 1)
				AppendMenu(m, MF_STRING, 12, L"Start Octave...");
			int tcmd = TrackPopupMenu(m, TPM_CENTERALIGN | TPM_RETURNCMD, p.x, p.y, 0, hParent, 0);
			DestroyMenu(m);
			if (tcmd == 11)
			{
				vector<wchar_t> re(1000);
				if (!AskText(hParent, L"Velocity", L"Enter velocity (0-127):", re.data()))
					return;
				DefPianoVelocity = _wtoi(re.data());
				if (DefPianoVelocity < 0 || DefPianoVelocity > 127)
					DefPianoVelocity = 127;
			}
			if (tcmd == 13)
			{
				vector<wchar_t> re(1000);
				if (!AskText(hParent, L"Channel", L"Enter channel (1-16):", re.data()))
					return;
				DefPianoChannel = _wtoi(re.data()) - 1;
				if (DefPianoChannel < 0 || DefPianoChannel > 15)
					DefPianoChannel = 0;
			}
			if (tcmd == 12)
			{
				vector<wchar_t> re(1000);
				if (!AskText(hParent, L"Octave", L"Enter starting octave (0-8):", re.data()))
					return;
				PianoStartOctave = _wtoi(re.data());
				if (PianoStartOctave < 0 || PianoStartOctave > 9)
					PianoStartOctave = 2;
				Redraw();
			}
		}

		void PaintSide(ID2D1RenderTarget * p, RECT rc)
		{
			CreateBrushes(p);
			// dirx  0 left 1 right
			DrawnPiano.clear();
			// Full
			if (side.Width == 0)
			{
				side.full = D2D1_RECT_F({});
				return;
			}
			int dirx = Direction;
			if (PianoPosition == 1)
				dirx = 2;
			if (PianoOnly)
			{
				dirx = 2;
				PianoPosition = 1;
			}

			if (dirx == 0)
			{
				side.full.left = (FLOAT)rc.left;
				side.full.top = (FLOAT)rc.top;
				side.full.bottom = (FLOAT)rc.bottom;
				side.full.right = (FLOAT)side.Width;
			}
			else
			if (dirx == 1)
			{
				side.full.left = (FLOAT)(rc.right - side.Width);
				side.full.top = (FLOAT)rc.top;
				side.full.bottom = (FLOAT)rc.bottom;
				side.full.right = (FLOAT)rc.right;
			}
			else
			if (dirx == 2)
			{
				if (PianoOnly == 0)
				{
					side.full.left = (FLOAT)rc.left;
					side.full.top = (FLOAT)rc.top + rc.bottom - side.Width;
					side.full.bottom = (FLOAT)rc.bottom;
					side.full.right = (FLOAT)rc.right;
				}
				
			}


			p->FillRectangle(side.full, SideBrush);
			if (dirx == 2)
			{
				// We paint horizontally from C
				float wnw = 25.0f;
				float X = side.full.left;

				// White Notes
				for (int oct = PianoStartOctave ; ; oct++)
				{
					for (int n = 0; n < 7; n++)
					{
						D2D1_RECT_F f;
						f.left = X;
						f.right = X + wnw - 1;
						f.top = side.full.top;
						f.bottom = side.full.bottom;

						DRAWPIANO dp;
						dp.full = f;
						if (n == 0) dp.m = (oct * 12) + 0;
						if (n == 1) dp.m = (oct * 12) + 2;
						if (n == 2) dp.m = (oct * 12) + 4;
						if (n == 3) dp.m = (oct * 12) + 5;
						if (n == 4) dp.m = (oct * 12) + 7;
						if (n == 5) dp.m = (oct * 12) + 9;
						if (n == 6) dp.m = (oct * 12) + 11;

						if (dp.m == PianoNoteClicked && PianoClicking)
							p->FillRectangle(f, LineBrush);
						else
							p->FillRectangle(f, WhiteBrush);

						DrawnPiano.push_back(dp);

						if (n == 0)
						{
							auto f4 = f;
							f4.bottom -= 5;
							f4.top = f4.bottom - 15;
							wchar_t ly[100] = { 0 };
							swprintf_s(ly, 100, L"C%i", oct - 1);
							Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
							Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
							if (dp.m == PianoNoteClicked && PianoClicking)
								p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f4, WhiteBrush);
							else
								p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f4, BlackBrush);
						}

						X += wnw;

						if (X >= side.full.right)
							break;
					}
					if (X >= side.full.right)
						break;
				}

				// Black notes
				for (size_t i = 0 ; i < DrawnPiano.size() ; i++)
				{
					auto& dpx = DrawnPiano[i];
					D2D1_RECT_F f = dpx.full;
					DRAWPIANO dp;
					if (!White(dpx.m))
						break;
					int nn = dpx.m % 12;
					if (nn == 0 || nn == 5) // C/F
					{
						f.left += wnw / 2.0f;
						f.right += wnw / 3.0f;
						f.bottom = f.top + (f.bottom - f.top) / 2.0f;
					}
					else
					if (nn == 7) // G
					{
						f.left += wnw / 2.0f;
						f.left += wnw / 8.0f;
						f.right += wnw / 2.0f;
						f.right -= wnw / 8.0f;
						f.bottom = f.top + (f.bottom - f.top) / 2.0f;
					}
					else
					if (nn == 2 || nn == 9) // D/A
					{
						f.left += 2*wnw / 3.0f;
						f.right += wnw / 2.0f;
						f.bottom = f.top + (f.bottom - f.top) / 2.0f;
					}
					else
						continue;

					dp.m = dpx.m + 1;
					dp.full = f;

					
					if (dp.m == PianoNoteClicked && PianoClicking)
						p->FillRectangle(f, LineBrush);
					else
						p->FillRectangle(f, BlackBrush);

					DrawnPiano.push_back(dp);
				}

				return;
			}

			// White keys
			if (DrawedNotes.empty())
				return;
			auto first = DrawedNotes[0];
			auto fn = first.n % 12;
			float HeightPerNote = HeightAtNote(0);
			float TotalOct = HeightPerNote * 12;
			float WhiteSize = TotalOct / 7.0f;
			if (fn == 2) // Start from D
			{
				TotalOct = HeightPerNote * 10;
				WhiteSize = TotalOct / 6.0f;
			}
			if (fn == 4) // Start from E
			{
				TotalOct = HeightPerNote * 8;
				WhiteSize = TotalOct / 5.0f;
			}
			if (fn == 5) // Start from F
			{
				TotalOct = HeightPerNote * 7;
				WhiteSize = TotalOct / 4.0f;
			}
			if (fn == 7) // Start from G
			{
				TotalOct = HeightPerNote * 5;
				WhiteSize = TotalOct / 3.0f;
			}
			if (fn == 9) // Start from A
			{
				TotalOct = HeightPerNote * 3;
				WhiteSize = TotalOct / 2.0f;
			}
			if (fn == 11) // Start from B
			{
				TotalOct = HeightPerNote * 1;
				WhiteSize = TotalOct / 1.0f;
			}

			float LeftWas = 0;
			int Added = 0;



			bool FirstEntry = true;
			for (auto& a : DrawedNotes)
			{
				int m = a.n % 12;
				//auto height = a.full.bottom - a.full.top;

				if (m == 0) // Reset sizes
				{
					TotalOct = HeightPerNote * 12;
					WhiteSize = TotalOct / 7.0f;
				}

				if (White(m))
				{
					auto d2 = side.full;
					d2.top = a.full.top;
					d2.bottom = a.full.bottom;

					d2.bottom += Added;
					d2.top += Added;
					Added = 0;

					if (FirstEntry)
					{
						FirstEntry = false;
						if (dirx == 1)
						{
							d2.bottom = d2.top + WhiteSize;
							LeftWas = d2.bottom;
						}
						else
						{
							d2.top = d2.bottom - WhiteSize;
							LeftWas = d2.top;
						}
					}
					else
					{
						if (dirx == 1)
						{
							d2.top = LeftWas;
							d2.bottom = d2.top + WhiteSize;
							LeftWas = d2.bottom;
						}
						else
						{
							d2.bottom = LeftWas;
							d2.top = d2.bottom - WhiteSize;
							LeftWas = d2.top;
						}
					}

					d2.top += 1;
					d2.bottom -= 1;

					DRAWPIANO dp;
					dp.full = d2;
					dp.m = a.n;
					DrawnPiano.push_back(dp);
					if (a.n == PianoNoteClicked && PianoClicking)
						p->FillRectangle(d2, LineBrush);
					else
						p->FillRectangle(d2, WhiteBrush);
					if (m == 0)
					{
						auto f4 = d2;
						f4.right -= 5;
						f4.left += 5;
						wchar_t ly[100] = { 0 };
						swprintf_s(ly, 100, L"C%i", (a.n / 12) - 1);
						if (dirx == 0)
							Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						else
							Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						if (a.n == PianoNoteClicked && PianoClicking)
							p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f4, WhiteBrush);
						else
							p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f4, BlackBrush);
					}

				}

			}

			// Blacks
			for (auto& a : DrawedNotes)
			{
				int m = a.n % 12;
				//auto height = a.full.bottom - a.full.top;
				if (m == 1 || m == 3 || m == 6 || m == 8 || m == 10)
				{
					auto d2 = side.full;
					d2.top = a.full.top;
					d2.bottom = a.full.bottom;
					d2.bottom += 1;
					d2.top -= 1;
					if (dirx == 0)
						d2.right = 2 * (d2.right - d2.left) / 3;
					else
						d2.left += 1 * (d2.right - d2.left) / 3;

					if (a.n == PianoNoteClicked && PianoClicking)
						p->FillRectangle(d2, LineBrush);
					else
						p->FillRectangle(d2, BlackBrush);
					DRAWPIANO dp;
					dp.full = d2;
					dp.m = a.n;
					DrawnPiano.push_back(dp);
				}

			}
		}

		void PaintTop(ID2D1RenderTarget * p, RECT rc)
		{
			// Full
			if (top.he == 0)
				return;
			if (top.he > 0)
			{
				top.full.left = (FLOAT)rc.left;
				if (Direction == 0 && PianoPosition == 0)
					top.full.left = side.full.right;
				top.full.top = (FLOAT)rc.top;
				top.full.right = (FLOAT)rc.right;
				top.full.bottom = top.full.top + top.he;
			}
			else
			{
				top.full.top = (FLOAT)rc.bottom + top.he;
				top.full.left = (FLOAT)rc.left;
				if (Direction == 0 && PianoPosition == 0)
					top.full.left = side.full.right;
				top.full.bottom = (FLOAT)rc.bottom;
				top.full.right = (FLOAT)rc.right;
			}



			p->FillRectangle(top.full, ScrollBrush);

			auto barr = top.full;

			float AvW = barr.right - barr.left;
			// How many measures are max?

			// We need TotalWidthForMusic
			// we have barr.right - barr.left
			// Left = the percentage hidden
			barr.left += AvW*((float)ScrollX/(float)TotalWidthForMusic);
			if (TotalWidthForMusic > AvW)
			{
				float P = (float)AvW/ (float)TotalWidthForMusic;
				barr.right = barr.left + AvW * P;
			}

			if (barr.left < top.full.left)
				barr.left = top.full.left;
			p->FillRectangle(barr, LineBrush);
		}


		void PaintInfo(ID2D1RenderTarget* p, RECT rc)
		{
			wchar_t ly[200] = { 0 };
			// Full
			if (info.he == 0)
				return;
			if (info.he > 0)
			{
				info.full.left = (FLOAT)rc.left;
				if (Direction == 0 && PianoPosition == 0)
					info.full.left = side.full.right;
				info.full.top = (FLOAT)rc.top;
				info.full.right = (FLOAT)rc.right;
				info.full.bottom = info.full.top + info.he;
			}
			else
			{
				info.full.top = (FLOAT)rc.bottom + info.he;
				info.full.left = (FLOAT)rc.left;
				if (Direction == 0 && PianoPosition == 0)
					info.full.left = side.full.right;
				info.full.bottom = (FLOAT)rc.bottom;
				info.full.right = (FLOAT)rc.right;
			}
			p->FillRectangle(info.full, WhiteBrush);

			if (DrawnMeasures.empty())
				return;

			D2D1_RECT_F f4;
			f4.left = info.full.left + 4;
			f4.right = info.full.right - 4;
			f4.top = info.full.top + 2;
			f4.bottom = info.full.bottom - 2;
			wchar_t* tls[] = {L"Auto",L"Eraser",L"Single entry",L"Quantizer",L"Paint"};
			KEY k0 = KeyAtMeasure(DrawnMeasures[0].im);
			TEMPO t0 = TempoAtMeasure(DrawnMeasures[0].im);
			wchar_t py[20] = { 0 };
			swprintf_s(py, 20, L"PART %u ", NextPart + 1);
			swprintf_s(ly, 200, L"%s %s L %u R%s%i %s %s", tls[(int)Tool],PartMode ? py : L"", NextLayer + 1, noteres > 0 ? L" 1/" : L" ", noteres > 0 ? noteres : -noteres,k0.Txt(),t0.Txt());
			Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f4, BlackBrush);

			// Bar except first
			for (size_t i = 1 ; i < DrawnMeasures.size() ; i++)
			{
				auto& d = DrawnMeasures[i];
				KEY k1 = KeyAtMeasure(d.im);
				if (k1 == k0)
					swprintf_s(ly, 200, L"%llu", (unsigned long long)d.im + 1);
				else
					swprintf_s(ly, 200, L"%llu %s", (unsigned long long)d.im + 1,k1.Txt());
				k0 = k1;

				TEMPO t1 = TempoAtMeasure(d.im);
				if (t1 == t0)
				{

				}
				else
				{
					swprintf_s(ly + wcslen(ly), 100 - wcslen(ly), L" %s", t1.Txt());
					t0 = t1;
				}

				D2D1_RECT_F f5 = f4;
				f5.left = d.full.left;
				p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f5, BlackBrush);

			}

			// Markers
			for (size_t i = 0; i < Markers.size(); i++)
			{
				D2D1_RECT_F fx;
				fx.left = PositionToX(Markers[i].p);
				if (fx.left < 0)
					continue;
				fx.left += 10;
				fx.right = info.full.right - 4;
				fx.top = info.full.top + 2;
				fx.bottom = info.full.bottom - 2;
				Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				p->DrawTextW(Markers[i].t.c_str(), (UINT32)Markers[i].t.length(), Text, fx, BlackBrush);
			}

		}

		float PositionToX(POSITION& p,bool Whole = false)
		{
			auto msr = DrawnMeasureByIndex(p.m);
			if (!msr)
			{
				if (!Whole)
					return -1;

				// Check everything
				float S = 0;
				for (size_t m = 0; m < p.m; m++)
				{
					auto ti = TimeAtMeasure(m);
					S += ti.nb * bw;
				}
				auto ti2 = TimeAtMeasure(p.m);
				float fwi = ti2.nb*bw;
				FRACTION fbr(ti2.nb, 4);
				// in fbr, full len
				// in p ?
				float S2 = S;
				S2 += fwi * (p.f / fbr).r();
				return S2;
			}

			D2D1_RECT_F f = msr->full;
			float fwi = (f.right - f.left);
			FRACTION fbr(msr->Beats.size(), 4);
			// in fbr, full len
			// in p ?
			f.left += fwi * (p.f / fbr).r();
			return f.left;
		}

		POSITION XTOPosition(float x)
		{
			return MeasureAndBarHitTest(x, true);
		}

		void PaintMini(ID2D1RenderTarget* p, D2D1_RECT_F rc, bool Sel,bool Mut, VISUALIZATIONPAINTINGPARAMETERS* vpp = 0)
		{
			CreateBrushes(p);
			//p->FillRectangle(rc, BlackBrush);

			int MinMidi = 128;
			int MaxMidi = 0;
			size_t MinBeats = 100000;
			size_t MaxBeats = 0;
			for (auto& n : notes)
			{
				if (n.midi < MinMidi)
					MinMidi = n.midi;
				if (n.midi > MaxMidi)
					MaxMidi = n.midi;

				ABSPOSITION a = AbsF(n.p);
				if (MinBeats > a.beats)
					MinBeats = a.beats;

				size_t abeatsd = (size_t)(a.beats + (n.d.r() * DENOM));

				if (MaxBeats < abeatsd)
					MaxBeats = abeatsd;


			}
			int mididiff = MaxMidi - MinMidi;
			if (mididiff <= 0)
				return; 
			size_t MaxP = MaxBeats - MinBeats;

			float MaxWidth = (rc.right - rc.left);
			float MaxHeight = (rc.bottom - rc.top) - 10;
			float HeightPerMidi = (float)MaxHeight / (float)(mididiff + 1);

			float WidthPerBeat = (float)MaxWidth / (float)MaxP;

			for (auto& n : notes) 
			{
				D2D1_RECT_F r2;
				
				// Height
				// In mididiff , MaxHeight
				// In zdiff    , ?

				float nm = (float)(n.midi - MinMidi);

				r2.top = rc.bottom - 5 -  HeightPerMidi*(nm + 1);
				r2.bottom = r2.top + HeightPerMidi/2.0f;

				// Position
				auto absn = AbsF(n.p);
				
				// In MaxP , MaxWidth
				// In absn , ?

				float bm = (float)(absn.beats - MinBeats);
				r2.left = rc.left + WidthPerBeat * bm;

				// Duration
				float bmx = (n.d.r() * DENOM);
				r2.right = r2.left + (WidthPerBeat * bmx);
				
				auto br = NoteBrush1;
				if (Mut)
					br = NoteBrush3;
				if (Sel)
				{
					br = NoteBrush2;
					if (Mut)
						br = NoteBrush4;
				}
				if (vpp && n.Selected)
					br = NoteBrush2;
				p->FillRectangle(r2, br);
			}
		}

		void Paint(ID2D1RenderTarget * p, RECT rc, unsigned long long param = 0)
		{
			rdr = rc;
			CreateBrushes(p);

			if (PianoOnly == 1)
			{
				side.Width = (int)(rc.right - rc.left);
				side.full.left = (FLOAT)rc.left;
				side.full.top = (FLOAT)rc.top;
				side.full.right = (FLOAT)rc.right;
				side.full.bottom = (FLOAT)rc.bottom;
				PaintSide(p, rc);
				return;
			}

			if (param == 1) // Move top paint
			{
				PaintTop(p, rc);
				return;
			}

			if (param == 2)
			{
				PaintSide(p, rc);
				return;

			}


			// Background
			p->Clear(bg);


			// Lines
			DrawedNotes.clear();
			for (auto c1 = FirstNote ; ; c1++)
			{
				if (c1 > 128)
					break;
				auto e = NotePos(c1);
				if (Direction == 0) // Down to up
				{
					if (e.top < rc.top)
						break;
				}
				else
				{
					if (e.bottom > rc.bottom)
						break;
				}
				// Paint only the up part
				D2D1_POINT_2F p1, p2;
				p1.x = e.left;
				p1.y = e.top;
				p2.x = e.right;
				p2.y = e.top;
				if ((c1 % 12) == 11 && Direction == 0)
					p->DrawLine(p1, p2, LineBrush,2.0f);
				else
				if ((c1 % 12) == 0 && Direction == 1)
					p->DrawLine(p1, p2, LineBrush, 2.0f);
				else
					p->DrawLine(p1, p2, LineBrush, 1.0f);

				DRAWNNOTES dn;
				dn.full = e;
				dn.n = c1;
				DrawedNotes.push_back(dn);
			}


			// Measures
			TotalWidthForMusic = 0;
			LeftWidthForMusic = 0;
			float StartX = (float)rc.left;
			if (Direction == 0 && PianoPosition == 0)
				StartX = (FLOAT)rc.left + (FLOAT)side.Width;
			DrawnMeasures.clear();
			int End = 0;
			int EndVisible = 0;
			auto FarStartX = StartX;
			StartX -= ScrollX;

			if (Direction == 0)
			{
				D2D1_POINT_2F p1, p2;
				p1.y = (FLOAT)rc.top;
				p1.x = StartX;
				p2.y = (FLOAT)rc.bottom;
				p2.x = StartX;
				p->DrawLine(p1, p2, LineBrush, MeasureStroke);
			}

			size_t LastMeasureWithNote = 0;
			if (!notes.empty())
			{
				LastMeasureWithNote = notes[notes.size() - 1].p.m;
			}

			for (size_t m = 0; ; m++)
			{
				auto time = TimeAtMeasure(m);
				bool WasDrown = false;
				DRAWNMEASURESANDBEATS dd;
				dd.im = m;
				//	auto SaveStartX = StartX;
				for (int ib = 0; ib < time.nb; ib++)
				{
					float E = StartX + bw;
					if (E > rc.right && ib == 0)
					{
						EndVisible = 1;
						if (LastMeasureWithNote < m)
							End = 1;
						if (End)
							break;
					}
					D2D1_POINT_2F p1, p2;
					if (ib == 0)
					{
						dd.full.left = StartX;
						dd.full.top = (FLOAT)rc.top;
					}
					if (ib == (time.nb - 1))
					{
						dd.full.right = E;
						dd.full.bottom = (FLOAT)rc.bottom;
					}
					p1.x = E;
					p1.y = (FLOAT)rc.top;
					p2.x = E;
					p2.y = (FLOAT)rc.bottom;
					D2D1_RECT_F b;
					b.left = StartX;
					b.top = (FLOAT)rc.top;
					b.right = p2.x;
					b.bottom = (FLOAT)rc.bottom;

					DRAWNBEAT dbb;
					dbb.full = b;
					dd.Beats.push_back(dbb);
					if (E <= rc.right && p1.x > FarStartX)
					{
						WasDrown = true;
						p->DrawLine(p1, p2, LineBrush, ib == (time.nb - 1) ? MeasureStroke : BarStroke);
						if (snapres > 1 && E <= rc.right)
						{
							// From StartX to StartX + time.bw, small lines
							float bbw = bw / (float)snapres;
							auto pp1 = p1;
							auto pp2 = p2;
							pp1.x -= bw;
							pp2.x -= bw;
							for (size_t i = 0; i < (snapres - 1); i++)
							{
								pp1.x += bbw;
								pp2.x += bbw;
								if (pp1.x >= StartX)
									p->DrawLine(pp1, pp2, SnapLineBrush, BarStroke/2.0f);
							}
						}
					}
					StartX += bw;
				}
				if (End)
					break;
				if (LastMeasureWithNote >= m)
					TotalWidthForMusic += (size_t)(dd.full.right - dd.full.left);
				if (EndVisible == 0 && WasDrown)
					DrawnMeasures.push_back(dd);
			}

			// Markers
			for (auto& m : Markers)
			{
				auto x = PositionToX(m.p);
				m.VisiblePos = x;
				if (x < 0)
					continue;

				D2D1_POINT_2F p1, p2;
				p1.y = (FLOAT)rc.top;
				p1.x = x;
				p2.y = (FLOAT)rc.bottom;
				p2.x = x;
				p->DrawLine(p1, p2, WhiteBrush, MeasureStroke);
			}

			// Notes
			for (auto& n : notes)
			{
				n.dr.right = 0;
				n.dr.bottom = 0;
				auto msrbegin = DrawnMeasureByIndex(n.p.m);
				if (!msrbegin)
					continue;

				auto it = std::lower_bound(HiddenLayers.begin(), HiddenLayers.end(), n.layer);
				if (it != HiddenLayers.end() && *it == n.layer)
					continue;


				auto& msr = *msrbegin;
				D2D1_RECT_F f = msr.full;

				float fwi = (f.right - f.left);
				FRACTION fbr(msr.Beats.size(), 4);
				// in fbr, full len
				// in n.p ?
				f.left += fwi * (n.p.f / fbr).r();
				f.right = f.left + (bw * DENOM * n.d.r());

				// Find the note
				if (n.midi < FirstNote)
					continue;
				if ((n.midi - FirstNote) >= (int)DrawedNotes.size())
					continue;
				auto & dn = DrawedNotes[n.midi - FirstNote];

				// Adjust
				f.top = dn.full.top;
				f.bottom = dn.full.bottom;

				//f.left = msr.full;
				D2D1_ROUNDED_RECT fr;
				fr.rect = f;
				fr.radiusX = 4.0f;
				fr.radiusY = 4.0f;
				if (n.Selected)
					p->FillRoundedRectangle(fr, NoteBrush2);
				else
					p->FillRoundedRectangle(fr, NoteBrush1);
				n.dr = f;

				if (n.HasMetaEvent)
				{
					auto f4 = f;
					f4.left += 2;
					f4.right -= 2;
					f4.top += 10;
					f4.bottom = f.bottom - 13;

					wchar_t ly[100] = { 0 };
					vector<wchar_t> dx(n.MetaEventData.size() + 2);
					memcpy(dx.data(), n.MetaEventData.data(), n.MetaEventData.size());
					swprintf_s(ly, 100, L"FF %02u %u %s", n.MetaEvent,(unsigned long)n.MetaEventData.size(),dx.data());
					Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f4, BlackBrush);

				}

				bool IsAfterTouch = false;
				if ((n.nonote & 0xF0) == 0xA0)
					IsAfterTouch = true;

				bool IsCP = false;
				if ((n.nonote & 0xF0) == 0xC0)
					IsCP = true;

				bool IsPS = false;
				if ((n.nonote & 0xF0) == 0xE0)
					IsPS = true;

				if (n.nonote > 0 && !IsAfterTouch && !IsPS && !IsCP)
				{
					auto f4 = f;
					f4.left += 2;
					f4.right -= 2;
					f4.top += 10;
					f4.bottom = f.bottom - 13;

					wchar_t ly[100] = { 0 };
					swprintf_s(ly, 100, L"0x%06X", n.nonote);
					Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f4, BlackBrush);
				}

				if (n.nonote > 0 && IsCP)
				{
					auto f4 = f;
					f4.left += 2;
					f4.right -= 2;
					f4.top += 10;
					f4.bottom = f.bottom - 13;

					wchar_t ly[100] = { 0 };
					int y = (n.nonote >> 8) & 0xFF;
					if (y >= 127 || y < 0)
						y = 0;
					swprintf_s(ly, 100, L"0x%04X - %s", n.nonote,gmpa[y]);
					Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f4, BlackBrush);
				}

				if (IsAfterTouch)
				{
					auto f4 = f;
					f4.left += 2;
					f4.right -= 2;
					f4.top += 10;
					f4.bottom = f.bottom - 13;


					wchar_t ly[100] = { 0 };
					KEY k = KeyAtMeasure(n.p.m);
					MidiNoteName(ly, n.midi, k.k, k.m);

					wchar_t ly2[100] = { 0 };
					swprintf_s(ly2, 100, L"A-%s", ly);
					Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					p->DrawTextW(ly2, (UINT32)wcslen(ly2), Text, f4, BlackBrush);
				}

				if (IsPS)
				{
					auto f4 = f;
					f4.left += 2;
					f4.right -= 2;
					f4.top += 10;
					f4.bottom = f.bottom - 13;

					wchar_t ly2[100] = { 0 };
					int e = PitchShift(n.nonote);

					if (e == 0x2000)
						swprintf_s(ly2, 100, L"PS%u",n.ch);
					if (e < 0x2000)
						swprintf_s(ly2, 100, L"PS%u-%u", n.ch,0x2000 - e);
					if (e > 0x2000)
						swprintf_s(ly2, 100, L"PS%u+%u", n.ch, e - 0x2000);
					Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					p->DrawTextW(ly2, (UINT32)wcslen(ly2), Text, f4, BlackBrush);
				}

				// PS 
				if (IsPS)
				{
					auto f2 = f;
					f2.left += 10;
					f2.right -= 10;
					f2.top += (f2.bottom - f2.top) / 2 + 5;
					f2.bottom = f2.top + 3;
//					p->FillRectangle(f2, NoteBrush4);
				}

				// Velocity
				if (ViewVelocity && !IsPS && (IsAfterTouch || (n.nonote == 0 && !n.HasMetaEvent)))
				{
					auto f2 = f;
					f2.left += 10;
					f2.right -= 10;
					f2.top += (f2.bottom - f2.top) / 2 + 5;
					f2.bottom = f2.top + 3;
					// in 127, width full
					// in V, ? 
					float wf = (f2.right - f2.left) * n.vel / 127;
					p->FillRectangle(f2, NoteBrush3);

					f2.right = f2.left + wf;
					p->FillRectangle(f2, NoteBrush4);
				}

				// Channel
				if (ViewChannels && n.nonote == 0 && !n.HasMetaEvent)
				{
					auto f3 = f;
					f3.left += 10;
					f3.right -= 10;
					f3.top += 5;
					f3.bottom = f3.top + 3;
					float ChX = (f3.right - f3.left) / 16.0f;
					for (int ch = 0; ch <= 15; ch++)
					{
						f3.right = f3.left + ChX - 2;
						if (n.ch == ch)
							p->FillRectangle(f3, NoteBrush4);
						else
							p->FillRectangle(f3, NoteBrush3);
						f3.left += ChX;

					}
				}

				// Layer
				if (ViewLayers)
				{
					auto f4 = f;
					f4.left += 2;
					f4.right -= 2;
					f4.top += 10;
					f4.bottom = f.bottom - 13;

					wchar_t ly[100] = { 0 };
					if (n.nonote == 0 && !n.HasMetaEvent)
					{
						KEY k = KeyAtMeasure(n.p.m);
						MidiNoteName(ly, n.midi, k.k, k.m);
						Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f4, BlackBrush);
					}

					swprintf_s(ly, 100, L"%u", n.layer + 1);
					Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					p->DrawTextW(ly, (UINT32)wcslen(ly), Text, f4, BlackBrush);
				}
			}

			// Parts
			if (PartMode)
			{
				InvalidatePart();
				for (auto& pp : parts)
				{
					if (pp.second.full.right == 0)
						continue;

					D2D1_ROUNDED_RECT fr;
					fr.rect = pp.second.full;
					fr.radiusX = 4.0f;
					fr.radiusY = 4.0f;

					if (pp.second.S)
						p->FillRoundedRectangle(fr, PartBrush2);
					else
						p->FillRoundedRectangle(fr, PartBrush1);

					wchar_t ly[100] = { 0 };
					swprintf_s(ly, 100, L"Part %u", (unsigned long)(pp.first + 1));
					Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					if (pp.second.n.length())
						p->DrawTextW(pp.second.n.c_str(), (UINT32)pp.second.n.length(), Text, pp.second.full, WhiteBrush);
					else
						p->DrawTextW(ly, (UINT32)wcslen(ly), Text, pp.second.full, WhiteBrush);
				}
			}

			// Last Note Over
			if (ViewLiveNotes == 1)
			{
				D2D1_RECT_F r;
				if (LastBeatOverIdx < DrawnMeasures.size())
				{
					auto& mm = DrawnMeasures[LastBeatOverIdx];
					FRACTION frx(mm.Beats.size(), DENOM);
					if (LastOverHP.f < frx)
					{
						r = mm.Beats[0].full;
						for (size_t a = 0 ; a < mm.Beats.size(); a++)
						{
							if (LastOverHP.f >= FRACTION(a,DENOM))
								r = mm.Beats[a].full;
						}
						if (LastNoteOverIdx < DrawedNotes.size())
						{
							r.top = DrawedNotes[LastNoteOverIdx].full.top;
							r.bottom = DrawedNotes[LastNoteOverIdx].full.bottom;

							Text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
							Text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

							wchar_t ly[100] = { 0 };
							KEY k = KeyAtMeasure(DrawnMeasures[LastBeatOverIdx].im);
							MidiNoteName(ly, LastNoteOver, k.k, k.m);

							p->DrawTextW(ly, (UINT32)wcslen(ly), Text, r, WhiteBrush);
						}
					}
				}
			}

			// Side bar
			PaintSide(p, rc);

			// Side bar
			PaintTop(p, rc);

			// Info bar
			auto rc2 = rc;
			rc2.top += (LONG)(top.full.bottom - top.full.top);
			PaintInfo(p, rc2);

			if (Selecting)
			{
				p->FillRectangle(SelectRect, this->LineBrush);

			}
		}
	};
}
