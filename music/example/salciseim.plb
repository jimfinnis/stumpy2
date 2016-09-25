<?xml version="1.0" encoding="UTF-8"?>
<java version="1.7.0_111" class="java.beans.XMLDecoder">
 <object class="org.pale.stumpy2.model.PatchLibrary$Memento">
  <void property="patchList">
   <object class="java.util.LinkedList">
    <void method="add">
     <object class="org.pale.stumpy2.model.Patch$Memento">
      <void property="componentList">
       <object class="java.util.LinkedList">
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento0">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento0"/>
            <string>output</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento0"/>
            <object class="java.awt.Point" id="Point0">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point0"/>
               <int>505</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point0"/>
               <int>543</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento0"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="0"/>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="4">
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>17</int>
              </void>
             </array>
            </void>
            <void index="3">
             <array class="int" length="2">
              <void index="0">
               <int>14</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="0"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento1">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento1"/>
            <string>chord</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento1"/>
            <object class="java.awt.Point" id="Point1">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point1"/>
               <int>328</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point1"/>
               <int>311</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento1"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="8">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>024</string>
               </void>
               <void property="name">
                <string>default chord</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>024</string>
               </void>
               <void property="name">
                <string>chord 1</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>034</string>
               </void>
               <void property="name">
                <string>chord 2</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>024</string>
               </void>
               <void property="name">
                <string>chord 3</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>2</string>
               </void>
               <void property="maxVal">
                <int>5</int>
               </void>
               <void property="name">
                <string>octave</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>5</int>
               </void>
               <void property="encodedValue">
                <string>y</string>
               </void>
               <void property="name">
                <string>inversions</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>6</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>print</string>
               </void>
              </object>
             </void>
             <void index="7">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="ID">
                <int>7</int>
               </void>
               <void property="encodedValue">
                <string>2</string>
               </void>
               <void property="name">
                <string>scale</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="84" id="StringArray0">
                 <void index="0">
                  <string>Enigmatic</string>
                 </void>
                 <void index="1">
                  <string>Ethiopian</string>
                 </void>
                 <void index="2">
                  <string>Major</string>
                 </void>
                 <void index="3">
                  <string>Chinese2</string>
                 </void>
                 <void index="4">
                  <string>MelodicMinor</string>
                 </void>
                 <void index="5">
                  <string>LydianAugmented</string>
                 </void>
                 <void index="6">
                  <string>Dorian</string>
                 </void>
                 <void index="7">
                  <string>LydianMinor</string>
                 </void>
                 <void index="8">
                  <string>Symmetrical</string>
                 </void>
                 <void index="9">
                  <string>LeadingWholeTone</string>
                 </void>
                 <void index="10">
                  <string>LocrianUltra</string>
                 </void>
                 <void index="11">
                  <string>Chahargah</string>
                 </void>
                 <void index="12">
                  <string>Spanish8Tone</string>
                 </void>
                 <void index="13">
                  <string>Arabian</string>
                 </void>
                 <void index="14">
                  <string>LocrianNatural</string>
                 </void>
                 <void index="15">
                  <string>Augmented</string>
                 </void>
                 <void index="16">
                  <string>Chinese1</string>
                 </void>
                 <void index="17">
                  <string>Algerian1</string>
                 </void>
                 <void index="18">
                  <string>Lydian</string>
                 </void>
                 <void index="19">
                  <string>Mongolian</string>
                 </void>
                 <void index="20">
                  <string>Japanese</string>
                 </void>
                 <void index="21">
                  <string>HarmonicMajor</string>
                 </void>
                 <void index="22">
                  <string>Pd</string>
                 </void>
                 <void index="23">
                  <string>Balinese</string>
                 </void>
                 <void index="24">
                  <string>Chromatic</string>
                 </void>
                 <void index="25">
                  <string>Romanian</string>
                 </void>
                 <void index="26">
                  <string>Todi</string>
                 </void>
                 <void index="27">
                  <string>MixolydianAugmented</string>
                 </void>
                 <void index="28">
                  <string>PentatonicMajor</string>
                 </void>
                 <void index="29">
                  <string>Altered</string>
                 </void>
                 <void index="30">
                  <string>LocrianMajor</string>
                 </void>
                 <void index="31">
                  <string>NeapolitanMinor</string>
                 </void>
                 <void index="32">
                  <string>Pelog</string>
                 </void>
                 <void index="33">
                  <string>LydianDominant</string>
                 </void>
                 <void index="34">
                  <string>Byzantine</string>
                 </void>
                 <void index="35">
                  <string>Blues</string>
                 </void>
                 <void index="36">
                  <string>HungarianMajor</string>
                 </void>
                 <void index="37">
                  <string>Kumoi</string>
                 </void>
                 <void index="38">
                  <string>HungarianGypsy</string>
                 </void>
                 <void index="39">
                  <string>Algerian</string>
                 </void>
                 <void index="40">
                  <string>Gypsy</string>
                 </void>
                 <void index="41">
                  <string>Pa</string>
                 </void>
                 <void index="42">
                  <string>Egyptian</string>
                 </void>
                 <void index="43">
                  <string>NaturalMajor</string>
                 </void>
                 <void index="44">
                  <string>Mixolydian</string>
                 </void>
                 <void index="45">
                  <string>LocrianSuper</string>
                 </void>
                 <void index="46">
                  <string>Hindu</string>
                 </void>
                 <void index="47">
                  <string>Mohammedan</string>
                 </void>
                 <void index="48">
                  <string>Locrian</string>
                 </void>
                 <void index="49">
                  <string>Pfcg</string>
                 </void>
                 <void index="50">
                  <string>Minor</string>
                 </void>
                 <void index="51">
                  <string>Aeolian</string>
                 </void>
                 <void index="52">
                  <string>Overtone</string>
                 </void>
                 <void index="53">
                  <string>NeapolitanMajor</string>
                 </void>
                 <void index="54">
                  <string>Phrygian</string>
                 </void>
                 <void index="55">
                  <string>Algerian2</string>
                 </void>
                 <void index="56">
                  <string>InvertedDiminished</string>
                 </void>
                 <void index="57">
                  <string>Spanish</string>
                 </void>
                 <void index="58">
                  <string>BebopDominant</string>
                 </void>
                 <void index="59">
                  <string>Pe</string>
                 </void>
                 <void index="60">
                  <string>HarmonicMinor</string>
                 </void>
                 <void index="61">
                  <string>Diminished</string>
                 </void>
                 <void index="62">
                  <string>WholeTone</string>
                 </void>
                 <void index="63">
                  <string>BebopDominantFlatNine</string>
                 </void>
                 <void index="64">
                  <string>Indian</string>
                 </void>
                 <void index="65">
                  <string>Chinese</string>
                 </void>
                 <void index="66">
                  <string>Javanese</string>
                 </void>
                 <void index="67">
                  <string>BebopMinor</string>
                 </void>
                 <void index="68">
                  <string>HungarianMinor</string>
                 </void>
                 <void index="69">
                  <string>Flamenco</string>
                 </void>
                 <void index="70">
                  <string>PentatonicMinor</string>
                 </void>
                 <void index="71">
                  <string>NaturalMinor</string>
                 </void>
                 <void index="72">
                  <string>Iwato</string>
                 </void>
                 <void index="73">
                  <string>Marva</string>
                 </void>
                 <void index="74">
                  <string>Persian</string>
                 </void>
                 <void index="75">
                  <string>PhrygianMajor</string>
                 </void>
                 <void index="76">
                  <string>BebopMajor</string>
                 </void>
                 <void index="77">
                  <string>DoubleHarmonic</string>
                 </void>
                 <void index="78">
                  <string>Pb</string>
                 </void>
                 <void index="79">
                  <string>Oriental</string>
                 </void>
                 <void index="80">
                  <string>BebopTonicMinor</string>
                 </void>
                 <void index="81">
                  <string>Ionian</string>
                 </void>
                 <void index="82">
                  <string>Hirajoshi</string>
                 </void>
                 <void index="83">
                  <string>Jewish</string>
                 </void>
                </array>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="2">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>5</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>8</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="1" id="booleanArray0"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento2">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento2"/>
            <string>clock</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento2"/>
            <object class="java.awt.Point" id="Point2">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point2"/>
               <int>472</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point2"/>
               <int>7</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento2"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="4">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>1</string>
               </void>
               <void property="maxVal">
                <int>4</int>
               </void>
               <void property="minVal">
                <int>-4</int>
               </void>
               <void property="name">
                <string>poweroftwo</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>1.0</string>
               </void>
               <void property="maxVal">
                <double>3.0</double>
               </void>
               <void property="minVal">
                <double>0.10000000149011612</double>
               </void>
               <void property="name">
                <string>mul</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>100.0</double>
               </void>
               <void property="minVal">
                <double>-100.0</double>
               </void>
               <void property="name">
                <string>add</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="name">
                <string>gapbeats</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="0"/>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="4"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento3">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento3"/>
            <string>thuemorse</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento3"/>
            <object class="java.awt.Point" id="Point3">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point3"/>
               <int>321</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point3"/>
               <int>195</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento3"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="5">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>8</string>
               </void>
               <void property="maxVal">
                <int>100</int>
               </void>
               <void property="minVal">
                <int>3</int>
               </void>
               <void property="name">
                <string>length</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>10</string>
               </void>
               <void property="maxVal">
                <int>10</int>
               </void>
               <void property="minVal">
                <int>2</int>
               </void>
               <void property="name">
                <string>depth</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>0123456789</string>
               </void>
               <void property="name">
                <string>perms</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>symmetric</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>auto regen</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="4">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>4</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="4" id="booleanArray1"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento4">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento4"/>
            <string>clockdiv</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento4"/>
            <object class="java.awt.Point" id="Point4">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point4"/>
               <int>441</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point4"/>
               <int>88</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento4"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="1">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>16</string>
               </void>
               <void property="maxVal">
                <int>32</int>
               </void>
               <void property="minVal">
                <int>1</int>
               </void>
               <void property="name">
                <string>div</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="1">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>2</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="1"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento5">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento5"/>
            <string>denpick</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento5"/>
            <object class="java.awt.Point" id="Point5">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point5"/>
               <int>316</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point5"/>
               <int>248</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento5"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="3">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>0000123444</string>
               </void>
               <void property="name">
                <string>vals</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>unit in</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>y</string>
               </void>
               <void property="name">
                <string>cycle</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="2">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>3</int>
              </void>
             </array>
            </void>
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>3</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="2" id="booleanArray2"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento6">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento6"/>
            <string>chordplay</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento6"/>
            <object class="java.awt.Point" id="Point6">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point6"/>
               <int>390</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point6"/>
               <int>467</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento6"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="7">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>1</string>
               </void>
               <void property="maxVal">
                <int>15</int>
               </void>
               <void property="name">
                <string>channel</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="name">
                <string>gapsecs</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>50.0</string>
               </void>
               <void property="maxVal">
                <double>64.0</double>
               </void>
               <void property="name">
                <string>vel</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>64.0</double>
               </void>
               <void property="minVal">
                <double>-64.0</double>
               </void>
               <void property="name">
                <string>velmod</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>0.4753000008687377</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="minVal">
                <double>0.10000000149011612</double>
               </void>
               <void property="name">
                <string>duration</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>5</int>
               </void>
               <void property="encodedValue">
                <string>3</string>
               </void>
               <void property="maxVal">
                <int>4</int>
               </void>
               <void property="name">
                <string>duration-pow2</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>6</int>
               </void>
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="maxVal">
                <int>24</int>
               </void>
               <void property="minVal">
                <int>-24</int>
               </void>
               <void property="name">
                <string>transpose</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="4">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>9</int>
              </void>
             </array>
            </void>
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>5</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="1"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento7">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento7"/>
            <string>thuemorse</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento7"/>
            <object class="java.awt.Point" id="Point7">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point7"/>
               <int>446</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point7"/>
               <int>195</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento7"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="5">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>8</string>
               </void>
               <void property="maxVal">
                <int>100</int>
               </void>
               <void property="minVal">
                <int>3</int>
               </void>
               <void property="name">
                <string>length</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>10</string>
               </void>
               <void property="maxVal">
                <int>10</int>
               </void>
               <void property="minVal">
                <int>2</int>
               </void>
               <void property="name">
                <string>depth</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>0123456789</string>
               </void>
               <void property="name">
                <string>perms</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>symmetric</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>auto regen</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="4">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>4</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <object idref="booleanArray1"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento8">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento8"/>
            <string>denpick</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento8"/>
            <object class="java.awt.Point" id="Point8">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point8"/>
               <int>440</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point8"/>
               <int>249</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento8"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="3">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>0000001122</string>
               </void>
               <void property="name">
                <string>vals</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>unit in</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>y</string>
               </void>
               <void property="name">
                <string>cycle</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="2">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>7</int>
              </void>
             </array>
            </void>
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>7</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <object idref="booleanArray2"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento9">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento9"/>
            <string>barswitcher</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento9"/>
            <object class="java.awt.Point" id="Point9">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point9"/>
               <int>356</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point9"/>
               <int>402</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento9"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="2">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>11</string>
               </void>
               <void property="name">
                <string>durs</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>01010101</string>
               </void>
               <void property="name">
                <string>ins</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="7">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>7</int>
              </void>
              <void index="1">
               <int>2</int>
              </void>
             </array>
            </void>
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>1</int>
              </void>
             </array>
            </void>
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>10</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="2"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento10">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento10"/>
            <string>chord</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento10"/>
            <object class="java.awt.Point" id="Point10">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point10"/>
               <int>452</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point10"/>
               <int>354</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento10"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="8">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>024</string>
               </void>
               <void property="name">
                <string>default chord</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>024</string>
               </void>
               <void property="name">
                <string>chord 1</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>034</string>
               </void>
               <void property="name">
                <string>chord 2</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>024</string>
               </void>
               <void property="name">
                <string>chord 3</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>2</string>
               </void>
               <void property="maxVal">
                <int>5</int>
               </void>
               <void property="name">
                <string>octave</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>5</int>
               </void>
               <void property="encodedValue">
                <string>y</string>
               </void>
               <void property="name">
                <string>inversions</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>6</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>print</string>
               </void>
              </object>
             </void>
             <void index="7">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="ID">
                <int>7</int>
               </void>
               <void property="encodedValue">
                <string>50</string>
               </void>
               <void property="name">
                <string>scale</string>
               </void>
               <void property="valueArray">
                <object idref="StringArray0"/>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="2">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>11</int>
              </void>
             </array>
            </void>
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>8</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <object idref="booleanArray0"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento11">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento11"/>
            <string>add</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento11"/>
            <object class="java.awt.Point" id="Point11">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point11"/>
               <int>437</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point11"/>
               <int>302</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento11"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="4">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>100.0</double>
               </void>
               <void property="minVal">
                <double>-100.0</double>
               </void>
               <void property="name">
                <string>add 1</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>1.0</string>
               </void>
               <void property="maxVal">
                <double>100.0</double>
               </void>
               <void property="minVal">
                <double>-100.0</double>
               </void>
               <void property="name">
                <string>mul 1</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>9.0</string>
               </void>
               <void property="maxVal">
                <double>100.0</double>
               </void>
               <void property="minVal">
                <double>-100.0</double>
               </void>
               <void property="name">
                <string>add 2</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>1.0</string>
               </void>
               <void property="maxVal">
                <double>100.0</double>
               </void>
               <void property="minVal">
                <double>-100.0</double>
               </void>
               <void property="name">
                <string>mul 2</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="2">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>5</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="1"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento12">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento12"/>
            <string>noteplay</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento12"/>
            <object class="java.awt.Point" id="Point12">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point12"/>
               <int>589</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point12"/>
               <int>360</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento12"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="7">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="maxVal">
                <int>15</int>
               </void>
               <void property="name">
                <string>channel</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>50.0</string>
               </void>
               <void property="maxVal">
                <double>64.0</double>
               </void>
               <void property="name">
                <string>vel</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>64.0</double>
               </void>
               <void property="minVal">
                <double>-64.0</double>
               </void>
               <void property="name">
                <string>velmod</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>0.8254000002890826</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="minVal">
                <double>0.10000000149011612</double>
               </void>
               <void property="name">
                <string>duration</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>1</string>
               </void>
               <void property="maxVal">
                <int>4</int>
               </void>
               <void property="name">
                <string>duration-pow2</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>5</int>
               </void>
               <void property="encodedValue">
                <string>y</string>
               </void>
               <void property="name">
                <string>suppress retrig</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>6</int>
               </void>
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="maxVal">
                <int>24</int>
               </void>
               <void property="minVal">
                <int>-24</int>
               </void>
               <void property="name">
                <string>transpose</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="6">
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>13</int>
              </void>
             </array>
            </void>
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>13</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
            <void index="4">
             <array class="int" length="2">
              <void index="0">
               <int>9</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="1" id="booleanArray3"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento13">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento13"/>
            <string>thuemorse</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento13"/>
            <object class="java.awt.Point" id="Point13">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point13"/>
               <int>589</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point13"/>
               <int>285</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento13"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="5">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>29</string>
               </void>
               <void property="maxVal">
                <int>100</int>
               </void>
               <void property="minVal">
                <int>3</int>
               </void>
               <void property="name">
                <string>length</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>5</string>
               </void>
               <void property="maxVal">
                <int>10</int>
               </void>
               <void property="minVal">
                <int>2</int>
               </void>
               <void property="name">
                <string>depth</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>0123456789</string>
               </void>
               <void property="name">
                <string>perms</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>symmetric</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>auto regen</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="4">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>2</int>
              </void>
              <void index="1">
               <int>3</int>
              </void>
             </array>
            </void>
            <void index="3">
             <array class="int" length="2">
              <void index="0">
               <int>4</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="4" id="booleanArray4"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento14">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento14"/>
            <string>noteplay</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento14"/>
            <object class="java.awt.Point" id="Point14">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point14"/>
               <int>751</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point14"/>
               <int>360</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento14"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="7">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="maxVal">
                <int>15</int>
               </void>
               <void property="name">
                <string>channel</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>50.0</string>
               </void>
               <void property="maxVal">
                <double>64.0</double>
               </void>
               <void property="name">
                <string>vel</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>64.0</double>
               </void>
               <void property="minVal">
                <double>-64.0</double>
               </void>
               <void property="name">
                <string>velmod</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>0.8254000002890826</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="minVal">
                <double>0.10000000149011612</double>
               </void>
               <void property="name">
                <string>duration</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>1</string>
               </void>
               <void property="maxVal">
                <int>4</int>
               </void>
               <void property="name">
                <string>duration-pow2</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>5</int>
               </void>
               <void property="encodedValue">
                <string>y</string>
               </void>
               <void property="name">
                <string>suppress retrig</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>6</int>
               </void>
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="maxVal">
                <int>24</int>
               </void>
               <void property="minVal">
                <int>-24</int>
               </void>
               <void property="name">
                <string>transpose</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="6">
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>15</int>
              </void>
             </array>
            </void>
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>15</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
            <void index="4">
             <array class="int" length="2">
              <void index="0">
               <int>9</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <object idref="booleanArray3"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento15">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento15"/>
            <string>thuemorse</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento15"/>
            <object class="java.awt.Point" id="Point15">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point15"/>
               <int>762</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point15"/>
               <int>280</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento15"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="5">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>29</string>
               </void>
               <void property="maxVal">
                <int>100</int>
               </void>
               <void property="minVal">
                <int>3</int>
               </void>
               <void property="name">
                <string>length</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>6</string>
               </void>
               <void property="maxVal">
                <int>10</int>
               </void>
               <void property="minVal">
                <int>2</int>
               </void>
               <void property="name">
                <string>depth</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>0123456789</string>
               </void>
               <void property="name">
                <string>perms</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>symmetric</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>n</string>
               </void>
               <void property="name">
                <string>auto regen</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="4">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>2</int>
              </void>
              <void index="1">
               <int>3</int>
              </void>
             </array>
            </void>
            <void index="3">
             <array class="int" length="2">
              <void index="0">
               <int>4</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <object idref="booleanArray4"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento16">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento16"/>
            <string>env</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento16"/>
            <object class="java.awt.Point" id="Point16">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point16"/>
               <int>564</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point16"/>
               <int>415</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento16"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="3">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="encodedValue">
                <string>3</string>
               </void>
               <void property="name">
                <string>mode</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="4">
                 <void index="0">
                  <string>retrig</string>
                 </void>
                 <void index="1">
                  <string>noretrig</string>
                 </void>
                 <void index="2">
                  <string>freerun</string>
                 </void>
                 <void index="3">
                  <string>oneshot</string>
                 </void>
                </array>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>-2</string>
               </void>
               <void property="maxVal">
                <int>10</int>
               </void>
               <void property="minVal">
                <int>-4</int>
               </void>
               <void property="name">
                <string>rate powerof2</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.EnvelopeParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>0.0,0.0,10.0,1.0,10.0,1.0,10.0,0.0,10.0,0.0,10.0,0.0;</string>
               </void>
               <void property="name">
                <string>env</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="1"/>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="2"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento17">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento17"/>
            <string>vel</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento17"/>
            <object class="java.awt.Point" id="Point17">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point17"/>
               <int>566</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point17"/>
               <int>480</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento17"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="2">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="name">
                <string>vel</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>1.0</string>
               </void>
               <void property="maxVal">
                <double>5.0</double>
               </void>
               <void property="minVal">
                <double>-5.0</double>
               </void>
               <void property="name">
                <string>mod</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="5">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>16</int>
              </void>
             </array>
            </void>
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>6</int>
              </void>
             </array>
            </void>
            <void index="3">
             <array class="int" length="2">
              <void index="0">
               <int>12</int>
              </void>
             </array>
            </void>
            <void index="4">
             <array class="int" length="2">
              <void index="0">
               <int>14</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="1"/>
          </void>
         </object>
        </void>
       </object>
      </void>
      <void property="name">
       <string>untitled</string>
      </void>
     </object>
    </void>
   </object>
  </void>
 </object>
</java>
