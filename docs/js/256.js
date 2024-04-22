"use strict";(self.webpackChunksqueezelite_esp32_web_installer=self.webpackChunksqueezelite_esp32_web_installer||[]).push([[256],{256:(t,e,i)=>{i.r(e),i.d(e,{startProvisioning:()=>E});const r="00467768-6228-2272-4663-277478268000";var s;!function(t){t[t.AUTHORIZATION_REQUIRED=1]="AUTHORIZATION_REQUIRED",t[t.AUTHORIZED=2]="AUTHORIZED",t[t.PROVISIONING=3]="PROVISIONING",t[t.PROVISIONED=4]="PROVISIONED"}(s||(s={}));class a extends EventTarget{constructor(t,e){super(),this.device=t,this.logger=e,this.errorState=0,this.capabilities=0}get name(){return this.device.name}async initialize(){this.logger.log("Trying to connect to Improv BLE service"),this.device.addEventListener("gattserverdisconnected",(()=>{this.currentState!==s.PROVISIONED&&this.dispatchEvent(new CustomEvent("disconnect"))})),await this.device.gatt.connect();const t=await this.device.gatt.getPrimaryService(r);this._currentStateChar=await t.getCharacteristic("00467768-6228-2272-4663-277478268001"),this._errorStateChar=await t.getCharacteristic("00467768-6228-2272-4663-277478268002"),this._rpcCommandChar=await t.getCharacteristic("00467768-6228-2272-4663-277478268003"),this._rpcResultChar=await t.getCharacteristic("00467768-6228-2272-4663-277478268004");try{const e=await t.getCharacteristic("00467768-6228-2272-4663-277478268005"),i=await e.readValue();this.capabilities=i.getUint8(0)}catch(t){console.warn("Firmware not according to spec, missing capability support.")}this._currentStateChar.addEventListener("characteristicvaluechanged",(t=>this._handleImprovCurrentStateChange(t.target.value))),await this._currentStateChar.startNotifications(),this._errorStateChar.addEventListener("characteristicvaluechanged",(t=>this._handleImprovErrorStateChange(t.target.value))),await this._errorStateChar.startNotifications(),this._rpcResultChar.addEventListener("characteristicvaluechanged",(t=>this._handleImprovRPCResultChange(t.target.value))),await this._rpcResultChar.startNotifications();const e=await this._currentStateChar.readValue(),i=await this._errorStateChar.readValue();this._handleImprovCurrentStateChange(e),this._handleImprovErrorStateChange(i)}close(){this.device.gatt.connected&&(this.logger.debug("Disconnecting gatt"),this.device.gatt.disconnect())}identify(){this.sendRPC(2,new Uint8Array)}async provision(t,e){const i=new TextEncoder,r=i.encode(t),a=i.encode(e),n=new Uint8Array([r.length,...r,a.length,...a]);try{const t=await this.sendRPCWithResponse(1,n);return this.logger.debug("Provisioned! Disconnecting gatt"),this.currentState=s.PROVISIONED,this.dispatchEvent(new CustomEvent("state-changed")),this.device.gatt.disconnect(),this.dispatchEvent(new CustomEvent("disconnect")),this.nextUrl=t.values.length>0?t.values[0]:void 0,this.nextUrl}catch(t){return}}async sendRPCWithResponse(t,e){if(this._rpcFeedback)throw new Error("Only 1 RPC command that requires feedback can be active");return await new Promise(((i,r)=>{this._rpcFeedback={command:t,resolve:i,reject:r},this.sendRPC(t,e)}))}sendRPC(t,e){this.logger.debug("RPC COMMAND",t,e);const i=new Uint8Array([t,e.length,...e,0]);i[i.length-1]=i.reduce(((t,e)=>t+e),0),this.RPCResult=void 0,this._rpcCommandChar.writeValueWithoutResponse(i)}_handleImprovCurrentStateChange(t){const e=t.getUint8(0);this.logger.debug("improv current state",e),this.currentState=e,this.dispatchEvent(new CustomEvent("state-change"))}_handleImprovErrorStateChange(t){const e=t.getUint8(0);this.logger.debug("improv error state",e),this.errorState=e,0!==e&&this._rpcFeedback&&(this._rpcFeedback.reject(e),this._rpcFeedback=void 0)}_handleImprovRPCResultChange(t){this.logger.debug("improv RPC result",t);const e=t.getUint8(0),i={command:e,values:[]},r=t.getUint8(1),s=new TextDecoder;for(let e=0;e<r;){const r=t.getUint8(2+e),a=new Uint8Array(r),n=2+e+1;for(let e=0;e<r;e++)a[e]=t.getUint8(n+e);i.values.push(s.decode(a)),e+=r+1}this.RPCResult=i,this._rpcFeedback&&(this._rpcFeedback.command!==e&&this.logger.error("Received "),this._rpcFeedback.resolve(i),this._rpcFeedback=void 0)}}var n=i(655),o=i(392),c=i(936),d=i(887),h=i(968);class l extends d.M{}l.styles=[h.W],customElements.define("ib-dialog",l);var p=i(133),v=i(816);class u extends p.P{}u.styles=[v.W],customElements.define("ib-textfield",u);var g=i(929),_=i(688);class b extends g.X{}b.styles=[_.W],customElements.define("ib-button",b);var m=i(315),C=i(350);class S extends m.e{}S.styles=[C.W],customElements.define("ib-circular-progress",S);let y=class extends o.oi{constructor(){super(...arguments),this._state="CONNECTING",this._improvErrorState=0,this._improvCapabilities=0,this._busy=!1}render(){let t,e="",i=!1;return"CONNECTING"===this._state?(t=this._renderProgress("Connecting"),i=!0):"ERROR"===this._state?t=this._renderMessage("⚠️",`An error occurred. ${this._error}`,!0):this._improvCurrentState===s.AUTHORIZATION_REQUIRED?t=this._renderMessage("👉","Press the authorize button on the device",!1):this._improvCurrentState===s.AUTHORIZED?this._busy?(t=this._renderProgress("Provisioning"),i=!0):(e="Configure Wi-Fi",t=this._renderImprovAuthorized()):this._improvCurrentState===s.PROVISIONING?(t=this._renderProgress("Provisioning"),i=!0):t=this._improvCurrentState===s.PROVISIONED?this._renderImprovProvisioned():this._renderMessage("⚠️",`Unexpected state: ${this._state} - ${this._improvCurrentState}`,!0),o.dy`
      <ib-dialog
        open
        .heading=${e}
        scrimClickAction
        @closed=${this._handleClose}
        .hideActions=${i}
        >${t}</ib-dialog
      >
    `}_renderProgress(t){return o.dy`
      <div class="center">
        <div>
          <ib-circular-progress
            active
            indeterminate
            density="8"
          ></ib-circular-progress>
        </div>
        ${t}
      </div>
    `}_renderMessage(t,e,i){return o.dy`
      <div class="center">
        <div class="icon">${t}</div>
        ${e}
      </div>
      ${i&&o.dy`
        <ib-button
          slot="primaryAction"
          dialogAction="ok"
          label="Close"
        ></ib-button>
      `}
    `}_renderImprovAuthorized(){let t;switch(this._improvErrorState){case 3:t="Unable to connect";break;case 0:break;default:t=`Unknown error (${this._improvErrorState})`}return o.dy`
      <div>
        Enter the credentials of the Wi-Fi network that you want
        ${this.client.name||"your device"} to connect to.
        ${e=this._improvCapabilities,1==(1&e)?o.dy`
              <button class="link" @click=${this._identify}>
                Identify the device.
              </button>
            `:""}
      </div>
      ${t?o.dy`<p class="error">${t}</p>`:""}
      <ib-textfield label="Network Name" name="ssid"></ib-textfield>
      <ib-textfield
        label="Password"
        name="password"
        type="password"
      ></ib-textfield>
      <ib-button
        slot="primaryAction"
        label="Connect"
        @click=${this._provision}
      ></ib-button>
      <ib-button
        slot="secondaryAction"
        dialogAction="close"
        label="Cancel"
      ></ib-button>
    `;var e}_renderImprovProvisioned(){return o.dy`
      <div class="center">
        <div class="icon">${"🎉"}</div>
        Provisioned!
      </div>
      ${void 0===this.client.nextUrl?o.dy`
            <ib-button
              slot="primaryAction"
              dialogAction="ok"
              label="Close"
            ></ib-button>
          `:o.dy`
            <a
              href=${this.client.nextUrl}
              slot="primaryAction"
              class="has-button"
              dialogAction="ok"
            >
              <ib-button label="Next"></ib-button>
            </a>
          `}
    `}firstUpdated(t){super.firstUpdated(t),this.client.addEventListener("state-changed",(()=>{this._state="IMPROV-STATE",this._busy=!1,this._improvCurrentState=this.client.currentState})),this.client.addEventListener("error-changed",(()=>{this._improvErrorState=this.client.errorState,0!==this._improvErrorState&&(this._busy=!1)})),this.client.addEventListener("disconnect",(()=>{"IMPROV-STATE"===this._state&&this._improvCurrentState===s.PROVISIONED||(this._state="ERROR",this._error="Device disconnected.")})),this._connect()}async _connect(){try{await this.client.initialize(),this._improvCurrentState=this.client.currentState,this._improvErrorState=this.client.errorState,this._improvCapabilities=this.client.capabilities,this._state="IMPROV-STATE"}catch(t){this._state="ERROR",this._error=t.message}}async _provision(){this._busy=!0;try{await this.client.provision(this._inputSSID.value,this._inputPassword.value)}catch(t){}finally{this._busy=!1}}_identify(){this.client.identify()}updated(t){if(super.updated(t),t.has("_state")||"IMPROV-STATE"===this._state&&t.has("_improvCurrentState")){const t="IMPROV-STATE"===this._state?s[this._improvCurrentState]||"UNKNOWN":this._state;this.stateUpdateCallback({state:t})}if((t.has("_improvCurrentState")||t.has("_state"))&&"IMPROV-STATE"===this._state&&this._improvCurrentState===s.AUTHORIZED){const t=this._inputSSID;t.updateComplete.then((()=>t.focus()))}}_handleClose(){this.client.close(),this.parentNode.removeChild(this)}};y.styles=o.iv`
    :host {
      --mdc-dialog-max-width: 390px;
      --mdc-theme-primary: var(--improv-primary-color, #03a9f4);
      --mdc-theme-on-primary: var(--improv-on-primary-color, #fff);
    }
    ib-textfield {
      display: block;
    }
    ib-textfield {
      margin-top: 16px;
    }
    .center {
      text-align: center;
    }
    ib-circular-progress {
      margin-bottom: 16px;
    }
    a.has-button {
      text-decoration: none;
    }
    .icon {
      font-size: 50px;
      line-height: 80px;
      color: black;
    }
    .error {
      color: #db4437;
    }
    button.link {
      background: none;
      color: inherit;
      border: none;
      padding: 0;
      font: inherit;
      text-align: left;
      text-decoration: underline;
      cursor: pointer;
    }
  `,(0,n.gn)([(0,c.SB)()],y.prototype,"_state",void 0),(0,n.gn)([(0,c.SB)()],y.prototype,"_improvCurrentState",void 0),(0,n.gn)([(0,c.SB)()],y.prototype,"_improvErrorState",void 0),(0,n.gn)([(0,c.SB)()],y.prototype,"_improvCapabilities",void 0),(0,n.gn)([(0,c.SB)()],y.prototype,"_busy",void 0),(0,n.gn)([(0,c.IO)("ib-textfield[name=ssid]")],y.prototype,"_inputSSID",void 0),(0,n.gn)([(0,c.IO)("ib-textfield[name=password]")],y.prototype,"_inputPassword",void 0),y=(0,n.gn)([(0,c.Mo)("improv-wifi-provision-dialog")],y);const E=async t=>{let e;try{e=await navigator.bluetooth.requestDevice({filters:[{services:[r]}]})}catch(t){console.error("Failed to get device",t)}if(!e)return;const i=document.createElement("improv-wifi-provision-dialog");i.client=new a(e,console),i.stateUpdateCallback=e=>{((t,e,i,r)=>{r=r||{};const s=new CustomEvent("state-changed",{bubbles:void 0===r.bubbles||r.bubbles,cancelable:Boolean(r.cancelable),composed:void 0===r.composed||r.composed,detail:i});t.dispatchEvent(s)})(t,0,e)},document.body.appendChild(i)}}}]);
//# sourceMappingURL=256.js.map