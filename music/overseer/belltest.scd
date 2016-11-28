(
// http://sccode.org/1-4Q6
SynthDef(\risset, {|out= 0, pan= 0, freq= 400, amp= 1, dur= 2, t_trig= 1, gate=1|
	var amps= #[1, 0.67, 1, 1.8, 2.67, 1.67, 1.46, 1.33, 1.33, 1, 1.33];
	var durs= #[1.5, 0.9, 0.65, 0.55, 0.325, 0.35, 0.25, 0.2, 0.15, 0.1, 0.075];
	var frqs= #[0.5, 0.56, 1, 0.92, 1.19, 1.7, 2, 2.74, 3, 3.76, 4.07];
	var dets= #[0, 1, 0, 1.7, 0, 0, 0, 0, 0, 0, 0];
	var src= Mix.fill(11, {|i|
		var env= EnvGen.ar(Env.perc(0.005, dur*3*durs[i], amps[i], -4.5), t_trig);
		SinOsc.ar(freq*frqs[i]*2+dets[i], 0, amp*env*0.1);
	});
	var q = EnvGen.ar(Env.adsr(0,0.1,1,dur),gate,doneAction:2);
	Out.ar(out,src);
}).store;


SynthDef(\rissetsweet, {|out= 0, pan= 0, freq= 400, amp= 1, dur= 2, t_trig= 1, gate=1|
	var amps= #[1, 0.67, 1, 1.8, 2.67, 1.67, 1.46, 1.33, 1.33, 1, 1.33];
	var durs= #[2, 0.9, 0.65, 0.55, 0.325, 0.35, 0.25, 0.2, 0.15, 0.1, 0.075];
	var frqs= #[0.5, 0.5, 1.0, 1, 1, 1, 2, 2.74, 3, 3.76, 4.07]+((0!5+Array.rand(6,-5,5)));
	var dets= [0, 1, 0, 1.7, 0, 0, 0, 0, 0, 0, 0]+Array.rand(11,-10,10);
	var src= Mix.fill(11, {|i|
		var env= EnvGen.ar(Env.perc(0.005, dur*3*durs[i], amps[i], -0.1), t_trig);
		SinOsc.ar(freq*frqs[i]*2+dets[i], 0, amp*env*0.1);
	});

	var q = EnvGen.ar(Env.adsr(0,0.1,1,dur),gate,doneAction:2);

	Out.ar(out,src*q);
}).store;
)

0!4

(
Pbind(\instrument,\risset,
	\dur,0.2,\octave,6,
	\degree,Pseq([0,1,2,3,4,5,6,7])).play
)