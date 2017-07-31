
/*

make a sampler;
get the triad working;
get the triad spitting out a text string that will go back to OF

OSC sent:
-info about where the targets are located
-a string about the current triad

OSC received:
-current locs of all the moths
-when a thing is created and when a thing dies


*/


59%12

(
~coranglais = [
	//range from 40 to 70
	~ce3 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CE3.wav"),
	~cg3 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CG3.wav"),
	~cas3 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CAS3.wav"),
	~ccs4 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CCS4.wav"),
	~ce4 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CE4.wav"),
	~cg4 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CG4.wav"),
	~cas4 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CAS4.wav"),
	~ccs5 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CCS5.wav"),
	~ce5 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CE5.wav"),
	~cg5 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CG5.wav"),
	~cas5 = Buffer.read(s, thisProcess.nowExecutingPath.dirname +/+ "samples/WAVs/CAS5.wav"),
]
)


(
{
arg nn;
var scale = nn.linlin(40, 70, 0, 10);
	var buf = scale.round;
	var step = (scale - buf * 2).round;

	//remainder = remainder.linlin(40, 70, 0, 10);



	[buf, step];

	Synth(\coranglais, [bufnum: ~coranglais[buf].bufnum, rate:step.midiratio/3]);
}.value(40);
)



(
SynthDef(\coranglais, {
	arg bufnum, rate;
	var gate = 0;
	var sig = PlayBuf.ar(1, bufnum, rate, loop:1)!2;
	//sig = sig * EnvGen.kr(Env.adsr(3, 3, 0.5, 3), gate, doneAction:2);
	Out.ar(0, sig);

}).add;
)



