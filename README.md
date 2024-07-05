<p><H3>Bluetooth���g����ESP32��RTC��ݒ肷��</H3></p>
<p>
ESP32��Bluetooth�@�\���g�p���āARTC�Ɏ�����ݒ肷����@���Љ��BBluetooth�iBLE�j�ɂ�GATT�iGeneric Attribute Profile�j�Ƃ����K�i������<br>
���͂̃f�o�C�X���񋟂���T�[�r�X��F�m���邱�Ƃ��ł���B���̒���"current time"�Ƃ����T�[�r�X������A���̃T�[�r�X�ł́A�f�o�C�X�̎������Q�Ƃł���悤�ɂȂ��Ă���B<br>
�����ł́A���̃T�[�r�X��ESP32���Ɏ������A<a href="https://developer.chrome.com/docs/capabilities/bluetooth?hl=ja">Web Bluetooth</a>�̋@�\�𗘗p���āA
�O���̃u���E�U����A���ݎ�����ESP32��RTC�i�N���b�N�j�ɐݒ肷����@�ɂ��Đ�������B
</p>

<p><strong>"current time"�T�[�r�X�̎���</strong><br>
ESP32��Service"current time"�ACharacteristic�Ƃ���"current time"��ݒ肵��BLE�T�[�o�[���`����B���ݎ����̐ݒ��Ƃ���Descriptor��ǉ����Ă����B<br>
BLE�T�[�o�[�̃A�h�o�^�C�Y���X�^�[�g������ƁAESP32��"current time"�T�[�r�X���O������F�m�ł���悤�ɂȂ�B<br>
�O������A���ݎ�����Descriptor�ɏ������܂��ƁADescriptor�̃R�[���o�b�N�� onWrite()�֐��ɒʒm�����B<br>
</p>
<p><strong>H/W�\��</strong><br>
 �EESP32 DevkitC<br>
 �ESD1306 128x64 OLED�\�����u<br>
 �ELED<br>
  <ul>
   <li>BuitIn LED�F5(1k�����x�̒�R���o�R���Đڑ�)&nbsp;&nbsp;�g�p����ESP32�ɂ�BuitIn LED�������̂ŊO�t������</li>
   <li>Control�pLED�F17(1k�����x�̒�R���o�R���Đڑ�)</li>
  </ul>
</p>
<p>
<img src="./WebBLE_ESP32_Clock_1.JPG" width="500" height="360">
</p>
<p><strong>�u���E�U�̑���</strong><br>
  <ol>
   <li>Chrome���J����"Web_Bluetooth_Set_RTC.html"���h���b�O���h���b�v����B</li>
   <li>"Connect to ESP32"�{�^���������BBluetooth�f�o�C�X�̃X�L������ʂ��\�������B</li>
   <li>�X�L������ʂ�"ESP32_2"���\�������̂őI������"�y�A�ݒ�"�{�^���������B</li>
   <li>�ڑ���ԁi��30�b�ԁBBuitIn LED���_�Łj�ɂȂ�̂�"Set current time to ESP32 RTC"�{�^���������B</li>
   <li>���݂̎������\�������B</li>
  </ol>
  �Ȃ��AControl�pLED��z�������ꍇ��,�ڑ���Ԃɂ���"Execute specified command : on/off"�{�^����������Control�pLED���_������B<br>
  Command��"off"�Ɠ��͂���"Execute specified command : on/off"�{�^����������Control�pLED����������B<br>
  ����Command���s�@�\�́A�g�����đ��̐���@�\�ɂ����p�ł���B
</p>
<p>
<img src="./WebBLE_ESP32_Clock_2.jpg" width="800" height="360">
</p>
<p><strong>�ڑ�</strong><br>
OLED�\�����u�̐ڑ��͈ȉ��̒ʂ�B<br>
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
<p><strong>�C���X�g�[��</strong><br>
<ol>
<li>�R�[�h���AZIP�`���Ń_�E�����[�h</li>
<li>ArduinoIDE�ɂ����āA���C�u�����}�l�[�W������ȉ����������ăC���X�g�[������</li>
 <ul>
  <li>Adafruit_BusIO</li>
  <li>Adafruit_GFX</li>
  <li>Adafruit_SSD1306</li>
 </ul>
<li>ArduinoIDE����ESP32_WebBLE_clock_set_master.ino���J��</li>
<li>�u���؁E�R���p�C���v�ɐ���������A��U�A�u���O��t���ĕۑ��v���s��</li>
</ol>
</p>
<p><strong>�኱�̉��</strong><br>
�EPC�ɂ�Bluetooth�@�\��Bluetooth(5.0�ȍ~)��USB�h���O�����K�v�ł���B<br>
�E�u���E�U��Chrome�����łȂ��AEdge�ł����삵���B�X�}�[�g�t�H����Chrome�ł����삷��B<br>
�E�����Ŏg�p����"Web_Bluetooth_Set_RTC.html"�͖`����Web Bluetooth�T�C�g�̃T���v���������������̂ł���B<br>
</p>
<p><strong>���ӎ���</strong><br>
�E���p�̍ۂ́A���ȐӔC�ł��y���݂��������B<br>
</p>
