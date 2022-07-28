<!-- editor based on the one found here: https://codepen.io/AzazelN28/pen/mQMapb (MIT license) -->
<template>
  <div id="hexeditor">
    <div tabindex=0 class="file" v-if="dataView">
      <div class="offsets" title="Offset">
        <div class="offset" v-for="(offset, lineIndex) of offsets" :key="lineIndex" :class="{ 'active': isLineActive(lineIndex) }" @click="handleLineClick(lineIndex, $event)">{{offset}}</div>
      </div>
      <div class="lines hex" title="Hex value">
        <div class="line" v-for="(line, lineIndex) of hex" :key="lineIndex" :class="{ 'active': isLineActive(lineIndex) }" @click="handleLineClick(lineIndex, $event)">
          <div class="value" v-for="(value, valueIndex) of line" :key="(lineIndex * 16) + valueIndex" :class="{ 'active': isValueActive(lineIndex, valueIndex) }" @click="handleValueClick(valueIndex, $event)">{{value}}</div>
        </div>
      </div>
      <div class="lines ascii" title="Ascii value">
        <div class="line" v-for="(line, lineIndex) of ascii" :key="lineIndex" :class="{ 'active': isLineActive(lineIndex) }" @click="handleLineClick(lineIndex, $event)">
          <div class="value" v-for="(value, valueIndex) of line" :key="(lineIndex * 16) + valueIndex" :class="{ 'active': isValueActive(lineIndex, valueIndex) }" @click="handleValueClick(valueIndex, $event)">{{value}}</div>
        </div>
      </div>
    </div>
    <div class="interpreter" title="Data interpreter">
      <h2>Info</h2>
      <div class="offset">
        <div class="hex">{{offset.toString(16).padStart(8,'0')}} : {{size.toString(16).padStart(8,'0')}} bytes</div>
        <div class="dec">{{offset.toString().padStart(8,'0')}} : {{size.toString().padStart(8,'0')}} bytes</div>
      </div>
      <h2>Data Interpreter</h2>
      <form class="settings">
        <div class="settings-row">
          <fieldset class="setting endian">
            <legend>Endianness</legend>
            <div class="group">
              <input id="little-endian" type="checkbox" v-model="settings.le"/>
              <label id="little-endian-label" for="little-endian">Show little-endian</label>
            </div>
            <div class="group">
              <input id="big-endian" type="checkbox" v-model="settings.be"/>
              <label id="big-endian-label" for="little-endian">Show big-endian</label>
            </div>
          </fieldset>
          <fieldset class="setting sign">
            <legend>Signedness</legend>
            <div class="group">
              <input id="unsigned" type="checkbox" v-model="settings.u"/>
              <label id="unsigned-label" for="unsigned">Show unsigned</label>
            </div>
            <div class="group">
              <input id="signed" type="checkbox" v-model="settings.i"/>
              <label id="signed-label" for="signed">Show signed</label>
            </div>
          </fieldset>
        </div>
      </form>
      <table>
        <tr>
          <th>type</th>
          <th>value</th>
          <th>binary</th>
        </tr>
        <tr class="u8" title="8-bit unsigned int" v-if="settings.u">
          <td class="type">u8 </td>
          <td class="value">{{interpreter.u8}}</td>
          <td class="binary">{{interpreter.u8.toString(2).padStart(8,'0')}}</td>
        </tr>
        <tr class="i8" title="8-bit signed int" v-if="settings.i">
          <td class="type">i8 </td>
          <td class="value">{{interpreter.i8}}</td>
          <td class="binary">{{interpreter.i8.toString(2).padStart(8,'0')}}</td>
        </tr>
        <tr class="u16le" title="16-bit little endian unsigned int" v-if="settings.u &amp;&amp; settings.le">
          <td class="type">u16le </td>
          <td class="value">{{interpreter.u16le}}</td>
          <td class="binary">{{interpreter.u16le.toString(2).padStart(16,'0')}}</td>
        </tr>
        <tr class="i16le" title="16-bit little endian signed int" v-if="settings.i &amp;&amp; settings.le">
          <td class="type">i16le </td>
          <td class="value">{{interpreter.i16le}}</td>
          <td class="binary">{{interpreter.i16le.toString(2).padStart(16,'0')}}</td>
        </tr>
        <tr class="u16be" title="16-bit big endian unsigned int" v-if="settings.u &amp;&amp; settings.be">
          <td class="type">u16be</td>
          <td class="value">{{interpreter.u16be}}</td>
          <td class="binary">{{interpreter.u16be.toString(2).padStart(16,'0')}}</td>
        </tr>
        <tr class="i16be" title="16-bit big endian signed int" v-if="settings.i &amp;&amp; settings.be">
          <td class="type">i16be </td>
          <td class="value">{{interpreter.i16be}}</td>
          <td class="binary">{{interpreter.i16be.toString(2).padStart(16,'0')}}</td>
        </tr>
        <tr class="u32le" title="32-bit little endian unsigned int" v-if="settings.u &amp;&amp; settings.le">
          <td class="type">u32le </td>
          <td class="value">{{interpreter.u32le}}</td>
          <td class="binary">{{interpreter.u32le.toString(2).padStart(32,'0')}}</td>
        </tr>
        <tr class="i32le" title="32-bit little endian signed int" v-if="settings.i &amp;&amp; settings.le">
          <td class="type">i32le</td>
          <td class="value">{{interpreter.i32le}}</td>
          <td class="binary">{{interpreter.i32le.toString(2).padStart(32,'0')}}</td>
        </tr>
        <tr class="u32be" title="32-bit big endian unsigned int" v-if="settings.u &amp;&amp; settings.be">
          <td class="type">u32be</td>
          <td class="value">{{interpreter.u32be}}</td>
          <td class="binary">{{interpreter.u32be.toString(2).padStart(32,'0')}}</td>
        </tr>
        <tr class="i32be" title="32-bit big endian signed int" v-if="settings.i &amp;&amp; settings.be">
          <td class="type">i32be</td>
          <td class="value">{{interpreter.i32be}}</td>
          <td class="binary">{{interpreter.i32be.toString(2).padStart(32,'0')}}</td>
        </tr>
        <tr class="f32le" title="32-bit little endian float" v-if="settings.le">
          <td class="type">f32le </td>
          <td class="value">{{interpreter.f32le}}</td>
          <td class="binary">{{interpreter.u32le.toString(2).padStart(32,'0')}}</td>
        </tr>
        <tr class="f32be" title="32-bit big endian float" v-if="settings.be">
          <td class="type">f32be</td>
          <td class="value">{{interpreter.f32be}}</td>
          <td class="binary">{{interpreter.u32be.toString(2).padStart(32,'0')}}</td>
        </tr>
        <tr class="f64le" title="64-bit little endian float" v-if="settings.le">
          <td class="type">f64le </td>
          <td class="value">{{interpreter.f64le}}</td>
          <td class="binary">--</td>
        </tr>
        <tr class="f64be" title="64-bit big endian float" v-if="settings.be">
          <td class="type">f64be</td>
          <td class="value">{{interpreter.f64be}}</td>
          <td class="binary">--</td>
        </tr>
        <tr class="tu32le" title="32-bit little endian time (unsigned int 32)" v-if="settings.le">
          <td class="type">tu32le</td>
          <td class="value">{{interpreter.tu32le}}</td>
          <td class="binary">--</td>
        </tr>
        <tr class="tu32be" title="32-bit big endian time (unsigned int 32)" v-if="settings.be">
          <td class="type">tu32be</td>
          <td class="value">{{interpreter.tu32be}}</td>
          <td class="binary">--</td>
        </tr>
        <tr class="tf32le" title="32-bit little endian time (float 32)" v-if="settings.le">
          <td class="type">tf32le</td>
          <td class="value">{{interpreter.tf32le}}</td>
          <td class="binary">--</td>
        </tr>
        <tr class="tf32be" title="32-bit big endian time (float 32)" v-if="settings.be">
          <td class="type">tf32be</td>
          <td class="value">{{interpreter.tf64be}}</td>
          <td class="binary">--</td>
        </tr>
        <tr class="tf64le" title="64-bit little endian time (float 64)" v-if="settings.le">
          <td class="type">tf64le</td>
          <td class="value">{{interpreter.tf64le}}</td>
          <td class="binary">--</td>
        </tr>
        <tr class="tf64be" title="64-bit big endian time (float 64)" v-if="settings.be">
          <td class="type">tf64be</td>
          <td class="value">{{interpreter.tf64be}}</td>
          <td class="binary">--</td>
        </tr>
      </table>
    </div>
  </div>
</template>

<script>
DataView.prototype.getUint64 = function (byteOffset, littleEndian) {
  // split 64-bit number into two 32-bit (4-byte) parts
  const left = this.getUint32(byteOffset, littleEndian);
  const right = this.getUint32(byteOffset + 4, littleEndian);

  // combine the two 32-bit values
  const combined = littleEndian ? left + 2 ** 32 * right : 2 ** 32 * left + right;

  if (!Number.isSafeInteger(combined)) {
    console.warn(combined, 'exceeds MAX_SAFE_INTEGER. Precision may be lost');
  }

  return combined;
};

export default {
  name: 'HexEditor',
  props: {
    msg: String
  },
  created() {

 
  },
  mounted() {
    this.$el.querySelector(".file").addEventListener('keydown', this.handleKey);
    this.$el.querySelector(".file").addEventListener('wheel', this.handleWheel);
    window.addEventListener('resize', this.handleResize);
    this.handleResize();
  },
  methods: {
    getRows(fn) {
      if (!this.dataView) {
        return [];
      }
      const rows = [];
      for (let row = this.row.start; row < this.row.start + this.rows; row++) {
        const values = [];
        for (let column = 0; column < this.rowLength; column++) {
          const offset = row * this.rowLength + column;
          const value = offset < this.dataView.byteLength ? this.dataView.getUint8(offset) : '  ';
          values.push(fn(value));
        }
        rows.push(values);
      }
      return rows;
    },
    updateColumnToLine() {
      const offset = this.row.current * this.rowLength + this.column;
      if (offset >= this.dataView.byteLength) {
        this.column = this.dataView.byteLength % this.rowLength - 1;
      }
    },
    moveCharLeft() {
      this.column = Math.max(0, this.column - 1);
      this.updateInterpreter();
    },
    moveCharRight() {
      const newColumn = Math.min(this.rowLength - 1, this.column + 1);
      const offset = this.row.current * this.rowLength + newColumn;
      if (offset < this.dataView.byteLength) {
        this.column = newColumn;
      }
      this.updateInterpreter();
    },
    moveLineUp() {
      this.row.current = Math.max(0, this.row.current - 1);
      if (this.row.current < this.row.start) {
        this.row.start = this.row.current;
      }
      this.updateColumnToLine();
      this.updateInterpreter();
    },
    moveLineDown() {
      this.row.current = Math.min(this.maxRows, this.row.current + 1);
      if (this.row.current > this.row.start + (this.rows - 1)) {
        this.row.start = this.row.current - (this.rows - 1);
      }
      this.updateColumnToLine();
      this.updateInterpreter();
    },
    movePageUp() {
      this.row.start = Math.max(0, this.row.start - this.rows);
      this.row.current = this.row.start;
      this.updateColumnToLine();
      this.updateInterpreter();
    },
    movePageDown() {
      this.row.start = Math.min(this.maxStartRow, this.row.start + this.rows);
      this.row.current = this.row.start;
      this.updateColumnToLine();
      this.updateInterpreter();
    },
    moveToStart() {
      this.row.current = this.row.start = 0;
    },
    moveToEnd() {
      this.row.start = this.maxStartRow;
      this.row.current = this.maxRows;
    },
    goToChar(charIndex) {
      this.column = charIndex;
    },
    goToLineRelative(lineIndex) {
      this.row.current = this.row.start + lineIndex;
    },
    isValueActive(lineIndex, valueIndex) {
      if (!this.isLineActive(lineIndex)) {
        return false;
      }
      return valueIndex === this.column;
    },
    isLineActive(lineIndex) {
      return lineIndex === this.row.current - this.row.start;
    },
    updateInterpreter() {
      this.interpreter.u8 = this.dataView.getUint8(this.offset);
      this.interpreter.i8 = this.dataView.getInt8(this.offset);

      this.interpreter.u16le = this.dataView.getUint16(this.offset, true);
      this.interpreter.i16le = this.dataView.getInt16(this.offset, true);
      this.interpreter.u16be = this.dataView.getUint16(this.offset, false);
      this.interpreter.i16be = this.dataView.getInt16(this.offset, false);

      this.interpreter.u32le = this.dataView.getUint32(this.offset, true);
      this.interpreter.i32le = this.dataView.getInt32(this.offset, true);
      this.interpreter.u32be = this.dataView.getUint32(this.offset, false);
      this.interpreter.i32be = this.dataView.getInt32(this.offset, false);

      this.interpreter.f32le = this.dataView.getFloat32(this.offset, true);
      this.interpreter.f32be = this.dataView.getFloat32(this.offset, true);

      this.interpreter.f64le = this.dataView.getFloat64(this.offset, true);
      this.interpreter.f64be = this.dataView.getFloat64(this.offset, true);

      this.interpreter.tu32le = new Date(this.dataView.getUint32(this.offset, true));
      this.interpreter.tu32be = new Date(this.dataView.getUint32(this.offset, false));

      this.interpreter.tf32le = new Date(this.dataView.getFloat32(this.offset, true));
      this.interpreter.tf32be = new Date(this.dataView.getFloat32(this.offset, false));
      this.interpreter.tf64le = new Date(this.dataView.getFloat64(this.offset, true));
      this.interpreter.tf64be = new Date(this.dataView.getFloat64(this.offset, false));
    },
    loadFile(file) {
      const fr = new FileReader();
      fr.addEventListener('load', this.handleFile);
      fr.addEventListener('error', this.handleFile);
      fr.readAsArrayBuffer(file);
    },
    handleValueClick(valueIndex) {
      this.goToChar(valueIndex);
    },
    handleLineClick(lineIndex) {
      this.goToLineRelative(lineIndex);
    },
    handleResize() {
      this.rows = this.$el.querySelector('.file').clientHeight;
    },
    handleKey(e) {
      if (e.code === 'ArrowUp' || e.key === 'k') this.moveLineUp();
      else if (e.code === 'ArrowDown' || e.key === 'j') this.moveLineDown();

      if (e.code === 'ArrowLeft' || e.key === 'h') this.moveCharLeft();
      else if (e.code === 'ArrowRight' || e.key === 'l') this.moveCharRight();

      if (e.code === 'PageUp') this.movePageUp();
      else if (e.code === 'PageDown') this.movePageDown();

      if (e.key === 'g') this.moveToStart();
      else if (e.key === 'G') this.moveToEnd();
    },
    handleWheel(e) {
      if (e.deltaY < 0) this.moveLineUp();
      else this.moveLineDown();
    },
  },

  data() {
    return {
      dataView: new DataView(new ArrayBuffer(2048)),
      rowLength: 16,
      row: {
        start: 0,
        current: 0
      },
      rowCount: 0,

      column: 0,
      settings: {
        le: true,
        be: true,
        u: true,
        i: true,
        colorize: {
          enabled: false,
          palette: null 
        },
        refresh: false
      },


      interpreter: {
        u8: 0,
        i8: 0,
        u16le: 0,
        i16le: 0,
        u16be: 0,
        i16be: 0,
        u32le: 0,
        i32le: 0,
        u32be: 0,
        i32be: 0,
        f32le: 0,
        f32be: 0,
        f64le: 0,
        f64be: 0,
        tu32le: 0,
        tu32be: 0,
        tf32le: 0,
        tf32be: 0,
        tf64le: 0,
        tf64be: 0,
        binary: 0,
        hex: 0 } };


  },
  computed: {
    size() {
      if (!this.dataView) {
        return 0;
      }
      return this.dataView.byteLength;
    },
    offset() {
      return this.row.current * this.rowLength + this.column;
    },
    maxStartRow() {
      return this.maxRows - (this.rows - 1);
    },
    maxRows() {
      if (!this.dataView) {
        return 0;
      }
      return Math.floor(this.dataView.byteLength / this.rowLength);
    },
    rows: {
      get() {
        return this.rowCount;
      },
      set(value) {
        console.log('set rows', value);
        this.rowCount = Math.floor(value / 18);
      } 
    },
    offsets() {
      if (!this.dataView) {
        return [];
      }
      const rows = [];
      for (let row = this.row.start; row < this.row.start + this.rows; row++) {
        rows.push((row * this.rowLength).toString(16).padStart(8, '0'));
      }
      return rows;
    },
    hex() {
      return this.getRows(value => value.toString(16).padStart(2, '0').toUpperCase());
    },
    ascii() {
      return this.getRows(value => value >= 32 && value <= 127 ? String.fromCharCode(value) : '.');
    } 
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
#hexeditor {
  height: 100%;
  width: 100%;
  overflow: hidden;
  position: absolute;
  display: block;
}
.file {
  display: flex;
  flex-direction: row;
  width: 100%;
  display: flex;
  font-family: monospace;
  font-size: 0.8rem;
  height: 80%
}
.offsets {
  background: #222;
  color: #aaa;
  display: flex;
  flex-direction: column;
  align-items: flex-end;
  width: auto;
}
.offsets .offset {
  height: 18px;
  padding: 0 1rem;
}
.offsets .offset.active {
  background: #224;
  color: #bbf;
}
.lines.hex {
  background: #333;
  color: #bbb;
  display: flex;
  flex-direction: column;
}
.lines.hex .line {
  display: flex;
  flex-direction: row;
  padding: 0 1rem;
  height: 18px;

}
.lines.hex .line.active {
  background: #336;
  color: #bbf;
}
.lines.hex .line .value {
  margin: 0 0.5rem;
}
.lines.hex .line .value.active {
  background: #bbf;
  color: #336;
}
.lines.ascii {
  background: #373737;
  color: #bbb;
  display: flex;
  flex-direction: column;
}
.lines.ascii .line {
  display: flex;
  flex-direction: row;
  padding: 0 1rem;
  height: 18px;
}
.lines.ascii .line.active {
  background: #373766;
  color: #bbf;
}
.lines.ascii .line .value.active {
  background: #fbf;
  color: #373766;
}
.interpreter {
  height: 20%;
  overflow-y: auto;
  padding-right: 1rem;
  padding-left: 1rem;
  background: #444;
  color: #bbb;
}
.interpreter form {
  width: 100%;
  margin-bottom: 1rem;
}
.interpreter form .settings-row {
  display: flex;
  flex-direction: row;
}
.interpreter form .setting {
  display: flex;
  flex: 1 1 auto;
  max-width: 12rem;
}
.interpreter form legend {
  padding: 0 1rem;
}
.interpreter form fieldset {
  margin-bottom: 1rem;
  display: flex;
  flex-direction: column;
}
.interpreter form .group {
  display: flex;
}
.interpreter table {
  width: 100%;
  border-collapse: collapse;
}
.interpreter table tr:nth-child(2n+0) td {
  padding-top: 1rem;
}
.interpreter table tr:nth-child(2n+1) td {
  padding-bottom: 1rem;
  border-bottom: 1px solid #bbb;
}
.interpreter table tr th {
  border-bottom: 1px solid #bbb;
  padding-bottom: 0.5rem;
}
.interpreter table tr td,
.interpreter table tr th {
  text-align: left;
  padding-right: 1rem;
}
.interpreter table tr td:last-child,
.interpreter table tr th:last-child {
  padding-right: 0;
}
.interpreter table tr td:first-child,
.interpreter table tr th:first-child {
  text-align: right;
}
.interpreter .u8 .type,
.interpreter .i8 .type {
  color: #c66;
}
.interpreter .u8 .value,
.interpreter .i8 .value {
  color: #df9f9f;
}
.interpreter .u16le .type,
.interpreter .i16le .type {
  color: #c96;
}
.interpreter .u16le .value,
.interpreter .i16le .value {
  color: #dfbf9f;
}
.interpreter .u16be .type,
.interpreter .i16be .type {
  color: #cc6;
}
.interpreter .u16be .value,
.interpreter .i16be .value {
  color: #dfdf9f;
}
.interpreter .u32le .type,
.interpreter .i32le .type {
  color: #9c6;
}
.interpreter .u32le .value,
.interpreter .i32le .value {
  color: #bfdf9f;
}
.interpreter .u32be .type,
.interpreter .i32be .type {
  color: #6c6;
}
.interpreter .u32be .value,
.interpreter .i32be .value {
  color: #9fdf9f;
}
.interpreter .f32le .type,
.interpreter .f32be .type {
  color: #6c9;
}
.interpreter .f32le .value,
.interpreter .f32be .value {
  color: #9fdfbf;
}
.interpreter .f64le .type,
.interpreter .f64be .type {
  color: #6cc;
}
.interpreter .f64le .value,
.interpreter .f64be .value {
  color: #9fdfdf;
}
.interpreter .tu32le .type,
.interpreter .tu32be .type {
  color: #69c;
}
.interpreter .tu32le .value,
.interpreter .tu32be .value {
  color: #9fbfdf;
}
.interpreter .tf32le .type,
.interpreter .tf32be .type {
  color: #7070c2;
}
.interpreter .tf32le .value,
.interpreter .tf32be .value {
  color: #a6a6d9;
}
.interpreter .tf64le .type,
.interpreter .tf64be .type {
  color: #9970c2;
}
.interpreter .tf64le .value,
.interpreter .tf64be .value {
  color: #bfa6d9;
}
</style>
