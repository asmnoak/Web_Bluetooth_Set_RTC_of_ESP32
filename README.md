<p><H3>Bluetoothを使ってESP32のRTCを設定する</H3></p>
<p>
ESP32のBluetooth機能を使用して、RTCに時刻を設定する方法を紹介する。Bluetooth（BLE）にはGATT（Generic Attribute Profile）という規格があり<br>
周囲のデバイスが提供するサービスを認知することができる。その中に"current time"というサービスがあり、このサービスでは、デバイスの時刻が参照できるようになっている。<br>
ここでは、そのサービスをESP32側に実装し、<a href="https://developer.chrome.com/docs/capabilities/bluetooth?hl=ja">Web Bluetooth</a>の機能を利用して、
外部のブラウザから、現在時刻をESP32のRTC（クロック）に設定する方法について説明する。
</p>

<p><strong>"current time"サービスの実装</strong><br>
ESP32にService"current time"、Characteristicとして"current time"を設定したBLEサーバーを定義する。現在時刻の設定先としてDescriptorを追加しておく。<br>
BLEサーバーのアドバタイズをスタートさせると、ESP32の"current time"サービスが外部から認知できるようになる。<br>
外部から、現在時刻がDescriptorに書き込まれると、Descriptorのコールバックの onWrite()関数に通知される。<br>
</p>
<p><strong>H/W構成</strong><br>
 ・ESP32 DevkitC<br>
 ・SD1306 128x64 OLED表示装置<br>
 ・LED<br>
  <ul>
   <li>BuitIn LED：5(1kΩ程度の抵抗を経由して接続)&nbsp;&nbsp;使用したESP32にはBuitIn LEDが無いので外付けした</li>
   <li>Control用LED：17(1kΩ程度の抵抗を経由して接続)</li>
  </ul>
</p>
<p>
<img src="./WebBLE_ESP32_Clock_1.JPG" width="500" height="360">
</p>
<p><strong>ブラウザの操作</strong><br>
  <ol>
   <li>Chromeを開いて"Web_Bluetooth_Set_RTC.html"をドラッグ＆ドロップする。</li>
   <li>"Connect to ESP32"ボタンを押す。Bluetoothデバイスのスキャン画面が表示される。</li>
   <li>スキャン画面に"ESP32_2"が表示されるので選択して"ペア設定"ボタンを押す。</li>
   <li>接続状態（約30秒間。BuitIn LEDが点滅）になるので"Set current time to ESP32 RTC"ボタンを押す。</li>
   <li>現在の時刻が表示される。</li>
  </ol>
  なお、Control用LEDを配線した場合は,接続状態にして"Execute specified command : on/off"ボタンを押すとControl用LEDが点灯する。<br>
  Commandに"off"と入力して"Execute specified command : on/off"ボタンを押すとControl用LEDが消灯する。<br>
  このCommand実行機能は、拡張して他の制御機能にも利用できる。
</p>
<p>
<img src="./WebBLE_ESP32_Clock_2.jpg" width="800" height="360">
</p>
<p><strong>接続</strong><br>
OLED表示装置の接続は以下の通り。<br>
<p>
<table> 
<tr>
<td>I2C&nbsp;</td><td>ESP32</td>
</tr>
<tr>
<td>SCK</td><td>21</td>
<tr>
<tr>
<td>SDA</td><td>22</td>
<tr>
</table>
</p>
</p>
<p><strong>インストール</strong><br>
<ol>
<li>コードを、ZIP形式でダウンロード</li>
<li>ArduinoIDEにおいて、ライブラリマネージャから以下を検索してインストールする</li>
 <ul>
  <li>Adafruit_BusIO</li>
  <li>Adafruit_GFX</li>
  <li>Adafruit_SSD1306</li>
 </ul>
<li>ArduinoIDEからESP32_WebBLE_clock_set_master.inoを開く</li>
<li>「検証・コンパイル」に成功したら、一旦、「名前を付けて保存」を行う</li>
</ol>
</p>
<p><strong>若干の解説</strong><br>
・PCにはBluetooth機能かBluetooth(5.0以降)のUSBドングルが必要である。<br>
・ブラウザはChromeだけでなく、Edgeでも動作した。スマートフォンのChromeでも動作する。<br>
・ここで使用した"Web_Bluetooth_Set_RTC.html"は冒頭のWeb Bluetoothサイトのサンプルを改造したものである。<br>
</p>
<p><strong>注意事項</strong><br>
・利用の際は、自己責任でお楽しみください。<br>
</p>
