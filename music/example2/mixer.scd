Server.local.options.numInputBusChannels=6;
Server.internal.options.numInputBusChannels=6;

if(NetAddr.langPort != 57120){
	"Is there another sclang running? Can't connect.".postln;
	"Addr is ".post;
	NetAddr.langPort.postln;
	1.exit;
};

"SC_JACK_DEFAULT_INPUTS".setenv(
	[
		"PianoQuiet:0",
		"PianoQuiet:1",
		"PianoNormal:0",
		"PianoNormal:1",
		"zynaddsubfx:out_1",
		"zynaddsubfx:out_2"
	].join(",")
);

"SC_JACK_DEFAULT_OUTPUTS".setenv(
	[
		"system:playback_1",
		"system:playback_2"
	].join(",")
);


s.waitForBoot({
	var o1 = OSCFunc({|msg,time,addr,rport|
		msg=msg[1..];
		msg.postln;
		~amps.setn(msg); //setn because it's from an array
	},'/mix');
	var o2 = OSCFunc({|msg,time,addr,rport|
		~pans.setn(msg[1..]);
	},'/pan');

	~amps = Bus.control(s,8);
	~pans = Bus.control(s,8);

	~amps.set([1,1,1,1,1,1,1,1]);
	~pans.set([0,0,0,0,0,0,0,0]);

	{
		var pans = In.kr(~pans,3);
		var amps = In.kr(~amps,3);
		var sig1 = Balance2.ar(SoundIn.ar(0),SoundIn.ar(1),pans[0],amps[0]);
		var sig2 = Balance2.ar(SoundIn.ar(2),SoundIn.ar(3),pans[1],amps[1]);
		var sig3 = Balance2.ar(SoundIn.ar(4),SoundIn.ar(5),pans[2],amps[2]);
		var sig = sig1+sig2+sig3;

		sig = GVerb.ar(sig,roomsize:45,revtime:6.5,damping:0.5,inputbw:0.75,spread:15,drylevel:1,earlyreflevel:0.7,
			taillevel:0.3,maxroomsize:50,mul:0.5);

		Out.ar(0,sig);

	}.play;


});
