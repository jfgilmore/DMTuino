# DMTuino

Open-source psychedelic therapy light based upon [Light Stimulation Device (LSD)](AnthonyDavidAdams.com/lsd) by [Anthony David Adams](https://AnthonyDavidAdams.com) which seeks to emulate the features of the [Lucia No. 3](http://www.lucialightexperience.com/). Feeling some components and the power level required to run the original patented product are superfluous to it's function the code has been rewritten and the design modified.

The intention of the redesign is to create a cheaper more accessible design unrestricted by the patent governing the original invention. The code refactor is intended as personal practice in object oriented C++.

## DISClAIMER

Use this device at your own risk; FOR RESEARCH AND ENTERTAINMENT PURPOSES ONLY.

The assembled functional device may induce: fluttering of the eyes, hallucination of symbols, visions, and or strong emotions.
It is also possible that it may induce feelings of transcendence, or leaving the body.

These experiences can be confronting or frightening.
The user should be reminded that the experience is contained within their mind and that they can end the experience at any time.
The start/stop button can be pressed to end the program immediately.

Contraindications for those who have a history of seizures, and, or psychosis; including schizophrenia, bipolar disorder,
depression, anxiety, epilepsy, or autism. May be beneficial for those with anxiety or depression<sup>[source](https://www.frontiersin.org/articles/10.3389/fphar.2017.00974/full)</sup> but caution is advised.
Use the shortest setting as a test if you are unsure.

## HYPOTHETICAL BASIS

**Hypothesis**: induction of DMT production in the pineal gland by use of external stroboscopic light cycling through a variety of frequencies.

"Recently, increases in neural signal diversity, compared to those found in wakeful
rest, have been reported during psychedelic states."<sup>[source](https://www.biorxiv.org/content/biorxiv/early/2019/01/04/511766.full.pdf)</sup>

\- _Begin Translation_ "After a short test session, I was so impressed by the shapes and colors that
I really wanted to continue. In the second session with Lucia, in which I saw a five-eyed being, the idea for mine came to me directly...
After a half-hour light session, I was able to sit down straight away
and record my ideas without thinking about them - that wasn't possible in the past."
Susanne Arndt, 22 - _End Translation_<sup>[source](https://www.light-attendance.eu/assets/Bericht%20LichtreiseHochschule%20MU%20Buchner%2020150902%20de.pdf)</sup>

This suggests that if these brain wave patterns could be externally induced then a person could be inducted into a psychedelic state without the use of an exogenous entheogen.

It is suspected, although not yet proven that DMT is produced in the body in the pineal gland by natural processes most notably during sleep. This is hypothesised as the chemical origin of the genesis of dreams.

### Brain waves, the facts

#### Delta wave – (0.1 – 3 Hz)

- Related to sleep
- Lowers Thyroid Stimulating Hormone & therefore metabolism
- Increases growth hormone releasing hormone

#### Theta wave – (4 – 7 Hz)

- Associated with movement & REM sleep. Linked to memory formation and navigation.
- Increased by meditation.

#### Alpha wave – (8 – 15 Hz)

- Adult alpha 10Hz reduces during meditation (to 9Hz). Produced in occipital lobe by wakeful relaxation with eyes closed.

#### Mu wave – (7.5 – 12.5 Hz)

- Same as alpha but for motor cortex

#### SMR wave – (12.5 – 15.5 Hz)

- Sensorimotor cortex, produced when idle (while person is not moving and not watching others move)

#### Beta wave – (16 – 31 Hz)

- Normal waking consciousness, eyes open.

#### Gamma wave – (32 – 100 Hz)

- Normal waking consciousness, may participate in the formation of coherent, unified perception.
- Related to attention, and synchronous though across brain regions. May help with Alzheimer's.
- Increased in experienced meditators.

### Discussion & Analysis

It appears that there is no direct corelation between the lights strobe frequency and the brain wave pattern induced. The alpha band light frequency (10Hz) has been shown to stimulate beta band waves (16-31Hz), and effect a decrease in alpha waves. The delta frequency of light strobe (3Hz) is correlated with increased beta and theta (4-7Hz) with a corresponding decrease in alpha to a greater extent than the alpha pattern. Delta waves seem unaffected by stroboscopic therapy. Longer continuous exposures to the delta strobe see beta waves decrease, perhaps as the brains experience with this pattern and approaches normal waking consciousness, a feature of the psychedelic experience, in opposition to an eyes closed relaxation state.

Psychedelic experiences are characterised by decreased alpha; **hypothesis**: other patterns may see correlation with the effects of meditation. So increased gamma, theta, beta and reduced alpha should be the aim. The existing material study on this therapy notably omitted data on the effect on gamma brain waves.

Negative correlation between beta and theta brain waves at the 10Hz strobe.

Changes in both the power spectrum and the phase spectrum contributed to the increases in EEG signal diversity.

Examining changes in the power spectrum during stroboscopic stimulation, we found a significant reduction in alpha power during 3 Hz stimulation, (relative to Dark, Fig 5), in which participants also reported the majority of CVH occurred.

10 Hz was characterized by high-intensity, simple SIVHs.
The 3 Hz condition was characterized by relatively low intensity, simple SIVHs, and fewer similarities to psilocybin-induced ASC, but interestingly, in addition, was associated with the occurrence of complex visual hallucinations (CVH).

## SOFTWARE CONFIGURATION

No WiFi or data cable connection is necessary to run the device.

### Sequences

```C++
const int sequence[frequency delay][duration in seconds]
```

a = alpha waves, b = beta waves,d = delta waves, t = theta waves, g = gamma waves
You can also input an integer as the desired delay time (on / off).

## HARDWARE

- 1 Arduino UNO
- 6 Coloured LEDs
- 3 Button switches
- 1 10kΩ resistor
- 6 220Ω resistors (can be up to 1kΩ)
