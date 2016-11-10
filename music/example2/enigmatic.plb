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
               <int>342</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point0"/>
               <int>988</int>
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
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>30</int>
              </void>
             </array>
            </void>
            <void index="3">
             <array class="int" length="2">
              <void index="0">
               <int>13</int>
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
            <string>clock</string>
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
               <int>248</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point1"/>
               <int>224</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento1"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="4">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>-4</string>
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
           <array class="boolean" length="4" id="booleanArray0"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento2">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento2"/>
            <string>noteplay</string>
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
               <int>210</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point2"/>
               <int>120</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento2"/>
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
                <string>0.20000000298023224</string>
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
                <string>4</string>
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
               <int>4</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
            <void index="2">
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
           <array class="boolean" length="1" id="booleanArray1"/>
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
               <int>307</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point3"/>
               <int>68</int>
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
                <string>5</string>
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
                <string>4</string>
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
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="4" id="booleanArray2"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento4">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento4"/>
            <string>perlin</string>
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
               <int>253</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point4"/>
               <int>25</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento4"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="7">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>2</string>
               </void>
               <void property="maxVal">
                <int>8</int>
               </void>
               <void property="minVal">
                <int>1</int>
               </void>
               <void property="name">
                <string>octaves</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>0.5</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="name">
                <string>persistence</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>2</int>
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
                <string>mul-in-x</string>
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
                <string>mul-in-y</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>4</int>
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
                <string>add-in</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>5</int>
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
                <string>mul-out</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>6</int>
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
                <string>add-out</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="2"/>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="2" id="booleanArray3"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento5">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento5"/>
            <string>noteplay</string>
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
               <int>46</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point5"/>
               <int>135</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento5"/>
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
                <string>0.20000000298023224</string>
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
                <string>4</string>
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
               <int>7</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>6</int>
              </void>
              <void index="1">
               <int>1</int>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento6">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento6"/>
            <string>thuemorse</string>
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
               <int>126</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point6"/>
               <int>75</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento6"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="5">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>5</string>
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
                <string>4</string>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento7">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento7"/>
            <string>perlin</string>
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
               <int>52</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point7"/>
               <int>19</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento7"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="7">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>2</string>
               </void>
               <void property="maxVal">
                <int>8</int>
               </void>
               <void property="minVal">
                <int>1</int>
               </void>
               <void property="name">
                <string>octaves</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>0.5</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="name">
                <string>persistence</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>2</int>
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
                <string>mul-in-x</string>
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
                <string>mul-in-y</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>4</int>
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
                <string>add-in</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>5</int>
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
                <string>mul-out</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>6</int>
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
                <string>add-out</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="2"/>
          </void>
          <void property="runOutputAlways">
           <object idref="booleanArray3"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento8">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento8"/>
            <string>denseq</string>
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
               <int>193</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point8"/>
               <int>275</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento8"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="1">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>001</string>
               </void>
               <void property="name">
                <string>seq</string>
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
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="5" id="booleanArray4"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento9">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento9"/>
            <string>denseq</string>
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
               <int>290</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point9"/>
               <int>276</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento9"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="1">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>0003</string>
               </void>
               <void property="name">
                <string>seq</string>
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
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="5" id="booleanArray5"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento10">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento10"/>
            <string>noteplay</string>
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
               <int>372</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point10"/>
               <int>122</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento10"/>
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
                <string>37.568</string>
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
                <string>27.007999999999996</string>
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
                <string>0.7246000004559755</string>
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
                <string>24</string>
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
               <int>12</int>
              </void>
             </array>
            </void>
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>12</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
            <void index="3">
             <array class="int" length="2">
              <void index="0">
               <int>11</int>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento11">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento11"/>
            <string>perlin</string>
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
               <int>422</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point11"/>
               <int>30</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento11"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="7">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>2</string>
               </void>
               <void property="maxVal">
                <int>8</int>
               </void>
               <void property="minVal">
                <int>1</int>
               </void>
               <void property="name">
                <string>octaves</string>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>0.5</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="name">
                <string>persistence</string>
               </void>
              </object>
             </void>
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>2</int>
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
                <string>mul-in-x</string>
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
                <string>mul-in-y</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>4</int>
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
                <string>add-in</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>5</int>
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
                <string>mul-out</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>6</int>
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
                <string>add-out</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="2"/>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="2"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento12">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento12"/>
            <string>thuemorse</string>
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
               <int>424</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point12"/>
               <int>75</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento12"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="5">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>7</string>
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
               <int>11</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="4"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento13">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento13"/>
            <string>chordstate</string>
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
               <int>440</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point13"/>
               <int>600</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento13"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="0"/>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="5">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>19</int>
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
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>2</int>
              </void>
             </array>
            </void>
            <void index="3">
             <array class="int" length="2">
              <void index="0">
               <int>10</int>
              </void>
             </array>
            </void>
            <void index="4">
             <array class="int" length="2">
              <void index="0">
               <int>28</int>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento14">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento14"/>
            <string>chord</string>
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
               <int>243</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point14"/>
               <int>342</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento14"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="9">
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
                <string>034</string>
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
                <string>024</string>
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
                <string>0</string>
               </void>
               <void property="name">
                <string>scale</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="84">
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
             <void index="8">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>8</int>
               </void>
               <void property="encodedValue">
                <string>1</string>
               </void>
               <void property="maxVal">
                <int>4</int>
               </void>
               <void property="minVal">
                <int>1</int>
               </void>
               <void property="name">
                <string>cycles</string>
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
               <int>9</int>
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
           <array class="boolean" length="1"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento15">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento15"/>
            <string>chord</string>
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
               <int>51</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point15"/>
               <int>344</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento15"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="9">
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
                <string>01467</string>
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
                <string>024</string>
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
                <string>5</string>
               </void>
               <void property="name">
                <string>scale</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="84">
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
             <void index="8">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>8</int>
               </void>
               <void property="encodedValue">
                <string>1</string>
               </void>
               <void property="maxVal">
                <int>4</int>
               </void>
               <void property="minVal">
                <int>1</int>
               </void>
               <void property="name">
                <string>cycles</string>
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
               <int>18</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>17</int>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento16">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento16"/>
            <string>clock</string>
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
               <int>70</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point16"/>
               <int>222</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento16"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="4">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>-4</string>
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
                <string>0.6800000011920929</string>
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
           <object idref="booleanArray0"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento17">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento17"/>
            <string>denseq</string>
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
               <int>15</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point17"/>
               <int>273</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento17"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="1">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>001</string>
               </void>
               <void property="name">
                <string>seq</string>
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
               <int>16</int>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento18">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento18"/>
            <string>denseq</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento18"/>
            <object class="java.awt.Point" id="Point18">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point18"/>
               <int>112</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point18"/>
               <int>274</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento18"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="1">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>0003</string>
               </void>
               <void property="name">
                <string>seq</string>
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
               <int>16</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <object idref="booleanArray5"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento19">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento19"/>
            <string>chordmorpher</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento19"/>
            <object class="java.awt.Point" id="Point19">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point19"/>
               <int>99</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point19"/>
               <int>426</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento19"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="3">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
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
                <string>mul</string>
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
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="maxVal">
                <int>1000</int>
               </void>
               <void property="name">
                <string>seed</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="9">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>25</int>
              </void>
             </array>
            </void>
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
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento20">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento20"/>
            <string>thuemorse</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento20"/>
            <object class="java.awt.Point" id="Point20">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point20"/>
               <int>537</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point20"/>
               <int>274</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento20"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="5">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>5</string>
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
                <string>4</string>
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
               <int>22</int>
              </void>
             </array>
            </void>
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>27</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="4" id="booleanArray6"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento21">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento21"/>
            <string>noteplay</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento21"/>
            <object class="java.awt.Point" id="Point21">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point21"/>
               <int>438</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point21"/>
               <int>373</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento21"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="7">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>7</string>
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
                <string>32.32</string>
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
                <string>0.22510000128299</string>
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
                <string>0</string>
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
               <int>20</int>
              </void>
             </array>
            </void>
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>20</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="1" id="booleanArray7"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento22">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento22"/>
            <string>clock</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento22"/>
            <object class="java.awt.Point" id="Point22">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point22"/>
               <int>470</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point22"/>
               <int>198</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento22"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="4">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>2</string>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento23">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento23"/>
            <string>thuemorse</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento23"/>
            <object class="java.awt.Point" id="Point23">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point23"/>
               <int>624</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point23"/>
               <int>276</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento23"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="5">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>6</string>
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
               <int>22</int>
              </void>
             </array>
            </void>
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>27</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <object idref="booleanArray6"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento24">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento24"/>
            <string>noteplay</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento24"/>
            <object class="java.awt.Point" id="Point24">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point24"/>
               <int>603</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point24"/>
               <int>376</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento24"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="7">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>7</string>
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
                <string>32.32</string>
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
                <string>0.22510000128299</string>
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
                <string>0</string>
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
                <string>12</string>
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
               <int>23</int>
              </void>
             </array>
            </void>
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>23</int>
              </void>
              <void index="1">
               <int>1</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <object idref="booleanArray7"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento25">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento25"/>
            <string>osc</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento25"/>
            <object class="java.awt.Point" id="Point25">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point25"/>
               <int>51</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point25"/>
               <int>521</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento25"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="8">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="name">
                <string>wave</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="5" id="StringArray0">
                 <void index="0">
                  <string>sin</string>
                 </void>
                 <void index="1">
                  <string>saw(ascending)</string>
                 </void>
                 <void index="2">
                  <string>saw(descending)</string>
                 </void>
                 <void index="3">
                  <string>triangle</string>
                 </void>
                 <void index="4">
                  <string>square</string>
                 </void>
                </array>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>0.01</string>
               </void>
               <void property="maxVal">
                <double>5.0</double>
               </void>
               <void property="name">
                <string>freq (beats)</string>
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
                <double>5.0</double>
               </void>
               <void property="minVal">
                <double>-5.0</double>
               </void>
               <void property="name">
                <string>phase</string>
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
                <double>5.0</double>
               </void>
               <void property="minVal">
                <double>-5.0</double>
               </void>
               <void property="name">
                <string>phase mod</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>1.0</string>
               </void>
               <void property="maxVal">
                <double>10.0</double>
               </void>
               <void property="name">
                <string>amp</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>5</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>5.0</double>
               </void>
               <void property="minVal">
                <double>-5.0</double>
               </void>
               <void property="name">
                <string>offset</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>6</int>
               </void>
               <void property="encodedValue">
                <string>y</string>
               </void>
               <void property="name">
                <string>min = zero</string>
               </void>
              </object>
             </void>
             <void index="7">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>7</int>
               </void>
               <void property="encodedValue">
                <string>0.5</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="name">
                <string>width (square)</string>
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
           <array class="boolean" length="1" id="booleanArray8"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento26">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento26"/>
            <string>osc</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento26"/>
            <object class="java.awt.Point" id="Point26">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point26"/>
               <int>21</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point26"/>
               <int>790</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>comment</string>
           <void method="set">
            <object idref="Component$Memento26"/>
            <string>quietpiano amp</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento26"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="8">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="name">
                <string>wave</string>
               </void>
               <void property="valueArray">
                <object idref="StringArray0"/>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>0.01</string>
               </void>
               <void property="maxVal">
                <double>5.0</double>
               </void>
               <void property="name">
                <string>freq (beats)</string>
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
                <double>5.0</double>
               </void>
               <void property="minVal">
                <double>-5.0</double>
               </void>
               <void property="name">
                <string>phase</string>
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
                <double>5.0</double>
               </void>
               <void property="minVal">
                <double>-5.0</double>
               </void>
               <void property="name">
                <string>phase mod</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>1.1600000000000001</string>
               </void>
               <void property="maxVal">
                <double>10.0</double>
               </void>
               <void property="name">
                <string>amp</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>5</int>
               </void>
               <void property="encodedValue">
                <string>-0.2</string>
               </void>
               <void property="maxVal">
                <double>5.0</double>
               </void>
               <void property="minVal">
                <double>-5.0</double>
               </void>
               <void property="name">
                <string>offset</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>6</int>
               </void>
               <void property="encodedValue">
                <string>y</string>
               </void>
               <void property="name">
                <string>min = zero</string>
               </void>
              </object>
             </void>
             <void index="7">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>7</int>
               </void>
               <void property="encodedValue">
                <string>0.5</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="name">
                <string>width (square)</string>
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
           <object idref="booleanArray8"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento27">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento27"/>
            <string>threshold</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento27"/>
            <object class="java.awt.Point" id="Point27">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point27"/>
               <int>568</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point27"/>
               <int>185</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento27"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="14">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
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
                <string>mul</string>
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
             <void index="2">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>2</int>
               </void>
               <void property="encodedValue">
                <string>0.1</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="minVal">
                <double>-1.0</double>
               </void>
               <void property="name">
                <string>level 0</string>
               </void>
              </object>
             </void>
             <void index="3">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="ID">
                <int>3</int>
               </void>
               <void property="encodedValue">
                <string>1</string>
               </void>
               <void property="name">
                <string>type 0</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="5">
                 <void index="0">
                  <string>inactive</string>
                 </void>
                 <void index="1">
                  <string>rising</string>
                 </void>
                 <void index="2">
                  <string>falling</string>
                 </void>
                 <void index="3">
                  <string>high</string>
                 </void>
                 <void index="4">
                  <string>low</string>
                 </void>
                </array>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="minVal">
                <double>-1.0</double>
               </void>
               <void property="name">
                <string>level 1</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="ID">
                <int>5</int>
               </void>
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="name">
                <string>type 1</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="5">
                 <void index="0">
                  <string>inactive</string>
                 </void>
                 <void index="1">
                  <string>rising</string>
                 </void>
                 <void index="2">
                  <string>falling</string>
                 </void>
                 <void index="3">
                  <string>high</string>
                 </void>
                 <void index="4">
                  <string>low</string>
                 </void>
                </array>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>6</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="minVal">
                <double>-1.0</double>
               </void>
               <void property="name">
                <string>level 2</string>
               </void>
              </object>
             </void>
             <void index="7">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="ID">
                <int>7</int>
               </void>
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="name">
                <string>type 2</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="5">
                 <void index="0">
                  <string>inactive</string>
                 </void>
                 <void index="1">
                  <string>rising</string>
                 </void>
                 <void index="2">
                  <string>falling</string>
                 </void>
                 <void index="3">
                  <string>high</string>
                 </void>
                 <void index="4">
                  <string>low</string>
                 </void>
                </array>
               </void>
              </object>
             </void>
             <void index="8">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>8</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="minVal">
                <double>-1.0</double>
               </void>
               <void property="name">
                <string>level 3</string>
               </void>
              </object>
             </void>
             <void index="9">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="ID">
                <int>9</int>
               </void>
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="name">
                <string>type 3</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="5">
                 <void index="0">
                  <string>inactive</string>
                 </void>
                 <void index="1">
                  <string>rising</string>
                 </void>
                 <void index="2">
                  <string>falling</string>
                 </void>
                 <void index="3">
                  <string>high</string>
                 </void>
                 <void index="4">
                  <string>low</string>
                 </void>
                </array>
               </void>
              </object>
             </void>
             <void index="10">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>10</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="minVal">
                <double>-1.0</double>
               </void>
               <void property="name">
                <string>level 4</string>
               </void>
              </object>
             </void>
             <void index="11">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="ID">
                <int>11</int>
               </void>
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="name">
                <string>type 4</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="5">
                 <void index="0">
                  <string>inactive</string>
                 </void>
                 <void index="1">
                  <string>rising</string>
                 </void>
                 <void index="2">
                  <string>falling</string>
                 </void>
                 <void index="3">
                  <string>high</string>
                 </void>
                 <void index="4">
                  <string>low</string>
                 </void>
                </array>
               </void>
              </object>
             </void>
             <void index="12">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>12</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="minVal">
                <double>-1.0</double>
               </void>
               <void property="name">
                <string>level 5</string>
               </void>
              </object>
             </void>
             <void index="13">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="ID">
                <int>13</int>
               </void>
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="name">
                <string>type 5</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="5">
                 <void index="0">
                  <string>inactive</string>
                 </void>
                 <void index="1">
                  <string>rising</string>
                 </void>
                 <void index="2">
                  <string>falling</string>
                 </void>
                 <void index="3">
                  <string>high</string>
                 </void>
                 <void index="4">
                  <string>low</string>
                 </void>
                </array>
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
               <int>26</int>
              </void>
             </array>
            </void>
           </array>
          </void>
          <void property="runOutputAlways">
           <array class="boolean" length="6"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento28">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento28"/>
            <string>mixer</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento28"/>
            <object class="java.awt.Point" id="Point28">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point28"/>
               <int>535</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point28"/>
               <int>536</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>comment</string>
           <void method="set">
            <object idref="Component$Memento28"/>
            <string>piano wibble</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento28"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="0"/>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="6">
            <void index="4">
             <array class="int" length="2">
              <void index="0">
               <int>21</int>
              </void>
             </array>
            </void>
            <void index="5">
             <array class="int" length="2">
              <void index="0">
               <int>24</int>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento29">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento29"/>
            <string>osc</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento29"/>
            <object class="java.awt.Point" id="Point29">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point29"/>
               <int>205</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point29"/>
               <int>790</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>comment</string>
           <void method="set">
            <object idref="Component$Memento29"/>
            <string>quietpiano pan</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento29"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="8">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.EnumParam$Memento">
               <void property="encodedValue">
                <string>0</string>
               </void>
               <void property="name">
                <string>wave</string>
               </void>
               <void property="valueArray">
                <array class="java.lang.String" length="5">
                 <void index="0">
                  <string>sin</string>
                 </void>
                 <void index="1">
                  <string>saw(ascending)</string>
                 </void>
                 <void index="2">
                  <string>saw(descending)</string>
                 </void>
                 <void index="3">
                  <string>triangle</string>
                 </void>
                 <void index="4">
                  <string>square</string>
                 </void>
                </array>
               </void>
              </object>
             </void>
             <void index="1">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>1</int>
               </void>
               <void property="encodedValue">
                <string>0.375</string>
               </void>
               <void property="maxVal">
                <double>5.0</double>
               </void>
               <void property="name">
                <string>freq (beats)</string>
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
                <double>5.0</double>
               </void>
               <void property="minVal">
                <double>-5.0</double>
               </void>
               <void property="name">
                <string>phase</string>
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
                <double>5.0</double>
               </void>
               <void property="minVal">
                <double>-5.0</double>
               </void>
               <void property="name">
                <string>phase mod</string>
               </void>
              </object>
             </void>
             <void index="4">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>4</int>
               </void>
               <void property="encodedValue">
                <string>1.0</string>
               </void>
               <void property="maxVal">
                <double>10.0</double>
               </void>
               <void property="name">
                <string>amp</string>
               </void>
              </object>
             </void>
             <void index="5">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>5</int>
               </void>
               <void property="encodedValue">
                <string>0.0</string>
               </void>
               <void property="maxVal">
                <double>5.0</double>
               </void>
               <void property="minVal">
                <double>-5.0</double>
               </void>
               <void property="name">
                <string>offset</string>
               </void>
              </object>
             </void>
             <void index="6">
              <object class="org.pale.stumpy2.model.paramtypes.BoolParam$Memento">
               <void property="ID">
                <int>6</int>
               </void>
               <void property="encodedValue">
                <string>y</string>
               </void>
               <void property="name">
                <string>min = zero</string>
               </void>
              </object>
             </void>
             <void index="7">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="ID">
                <int>7</int>
               </void>
               <void property="encodedValue">
                <string>0.5</string>
               </void>
               <void property="maxVal">
                <double>1.0</double>
               </void>
               <void property="name">
                <string>width (square)</string>
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
           <array class="boolean" length="1"/>
          </void>
         </object>
        </void>
        <void method="add">
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento30">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento30"/>
            <string>runslow</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento30"/>
            <object class="java.awt.Point" id="Point30">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point30"/>
               <int>257</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point30"/>
               <int>908</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento30"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="1">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.IntParam$Memento">
               <void property="encodedValue">
                <string>221</string>
               </void>
               <void property="maxVal">
                <int>1000</int>
               </void>
               <void property="minVal">
                <int>1</int>
               </void>
               <void property="name">
                <string>interval</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="6">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>31</int>
              </void>
             </array>
            </void>
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>32</int>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento31">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento31"/>
            <string>OSC-out</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento31"/>
            <object class="java.awt.Point" id="Point31">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point31"/>
               <int>48</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point31"/>
               <int>847</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento31"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="1">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>/mix</string>
               </void>
               <void property="name">
                <string>topic</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="6">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>26</int>
              </void>
             </array>
            </void>
            <void index="1">
             <array class="int" length="2">
              <void index="0">
               <int>33</int>
              </void>
             </array>
            </void>
            <void index="2">
             <array class="int" length="2">
              <void index="0">
               <int>33</int>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento32">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento32"/>
            <string>OSC-out</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento32"/>
            <object class="java.awt.Point" id="Point32">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point32"/>
               <int>224</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point32"/>
               <int>844</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento32"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="1">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.StringParam$Memento">
               <void property="encodedValue">
                <string>/pan</string>
               </void>
               <void property="name">
                <string>topic</string>
               </void>
              </object>
             </void>
            </array>
           </void>
          </void>
          <void property="inputData">
           <array class="[I" length="6">
            <void index="0">
             <array class="int" length="2">
              <void index="0">
               <int>29</int>
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
         <object class="org.pale.stumpy2.model.Component$Memento" id="Component$Memento33">
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>type</string>
           <void method="set">
            <object idref="Component$Memento33"/>
            <string>const</string>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>location</string>
           <void method="set">
            <object idref="Component$Memento33"/>
            <object class="java.awt.Point" id="Point33">
             <void class="java.awt.Point" method="getField">
              <string>x</string>
              <void method="set">
               <object idref="Point33"/>
               <int>112</int>
              </void>
             </void>
             <void class="java.awt.Point" method="getField">
              <string>y</string>
              <void method="set">
               <object idref="Point33"/>
               <int>787</int>
              </void>
             </void>
            </object>
           </void>
          </void>
          <void class="org.pale.stumpy2.model.Component$Memento" method="getField">
           <string>parameters</string>
           <void method="set">
            <object idref="Component$Memento33"/>
            <array class="org.pale.stumpy2.model.Parameter$Memento" length="1">
             <void index="0">
              <object class="org.pale.stumpy2.model.paramtypes.FloatParam$Memento">
               <void property="encodedValue">
                <string>1.0</string>
               </void>
               <void property="maxVal">
                <double>10.0</double>
               </void>
               <void property="minVal">
                <double>-10.0</double>
               </void>
               <void property="name">
                <string>val</string>
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
