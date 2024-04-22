// Load Styles
import '../scss/main.scss';
import escapeHtml from 'escape-html';
import { initBootstrap } from "./bootstrap.js";
//import 'improv-wifi-sdk';
//import 'improv-wifi-serial-sdk';
import $ from 'jquery';
//import { render } from 'sass';
//import 'crypto'; // Added in: node v14.17.0

window.jQuery = $;
window.$ = $;

const url = 'https://github.com/sle118/squeezelite-esp32/commit/'
// Loading bootstrap with optional features
initBootstrap({
  tooltip: true,
  popover: true,
  toasts: true,
});
function sortReleases(p1,p2){
  return p1.bits==p2.bits?0:p1.bits<p2.bits?-1:1
}

function getRevisionLine(description) {
  let table = ''
  description.split('\n').forEach(l => {
    let matches = /^(?<commit>[^\s]{7})\s(?<desc>.*)\((?<date>20\d{2}-\d{2}-\d{2}.*)\)\s\<(?<author>.*)\>/gm.exec(l)
    if (matches) {
      table += `<tr>
    <td><a href="${url}/${matches.groups.commit}">${matches.groups.commit}</a></td>
    <td>${escapeHtml(matches.groups.desc)}</td>
    <td>${matches.groups.date}</td>
    <td>${matches.groups.author}</td>
    </tr>`
    }
  })
  return table
 
}
function render_firmware_button(target,description,manifest,flash_button){

  let button= document.createElement('div')
  button.innerHTML=flash_button?`<div class="d-flex justify-content-between flex-row w-100 ">`:'';
  button.innerHTML+=`<div>${description}</div>`;
  button.innerHTML+=flash_button?`<div><esp-web-install-button   id="fb_${target}"   align = "center"  manifest="artifacts/${manifest}"  ></esp-web-install-button></div>`:'';
  return button;
}

function render_release_body(elem){
  let body=document.createElement('div');
  body.classList.add('accordion-body');
  body.id=`body_${elem.entry}`;
  let tble = document.createElement('table');
  tble.setAttribute('class',"table table-striped table-hover");
  tble.innerHTML= `
      <thead>
          <tr>
            <th>Commit</th>
            <th>Description</th>
            <th>Date</th>
            <th>Author</th>
          </tr>
        </thead>
        <tbody>
        ${getRevisionLine(elem.description)}
        </tbody>`;
  body.append(tble);
  return body; 
}
function render_release_table(platform,elem){
  let block = document.createElement('div');
  block.id=`ci_${elem.entry}`;
  block.setAttribute('class',"accordion-collapse collapse");
  block.setAttribute('aria-labelledby',`h${elem.entry}`);
  block.setAttribute('data-bs-parent',`#p${platform}`);
  block.setAttribute('associated_element',`${elem.entry}`);
  block.setAttribute('associated_platform',platform);
  block.setAttribute('manifest',`artifacts/${elem.manifest}`);
  block.append(render_release_body(elem));
  return block;
}
function render_platform_tab(id,active){
  let li_item= document.createElement('li');
  li_item.setAttribute('class',"nav-item");
  li_item.setAttribute('role',"presentation");
  
  li_item.innerHTML=  `<a class="nav-link  ${active?'active':''}" data-bs-toggle="tab" id="pill_${id}" href="#tab_${id}" aria-selected="true" role="tab">${id}</a>`;
  return li_item;
}

function render_release_button(elem){
  let rel_button= document.createElement('button');
  rel_button.setAttribute('class','accordion-button d-flex collapsed');
  rel_button.setAttribute('id',`button_${elem.entry}`);
  rel_button.setAttribute('type',"button");
  rel_button.setAttribute('data-bs-toggle',"collapse");
  rel_button.setAttribute('data-bs-target',`#ci_${elem.entry}`);
  rel_button.setAttribute('aria-expanded',false);
  rel_button.setAttribute('aria-controls',`ci_${elem.entry}`);
  rel_button.append(render_firmware_button(elem.entry,`Version ${elem.version} from branch ${elem.branch}, ${elem.bits} bits `,elem.manifest,false));
  return rel_button;
}
function render_release_header(platform,elem){
  let rel_head= document.createElement('h3');
  rel_head.setAttribute('class','accordion-header');
  rel_head.setAttribute('id',`h${elem.entry}`);
  rel_head.append(render_release_button(elem));
  return rel_head;
  
}
function render_release(platform,elem){
  let release = document.createElement('div');
  release.setAttribute('class',"accordion-item");
  release.setAttribute('id',`item_${elem.entry}`);
  release.append(render_release_header(platform,elem));
  release.append(render_release_table(platform,elem));

  return release;
}
function render_firmware_content(platform, releases,index){
  let content=document.createElement('div');
  content.setAttribute('class',"tab-pane fade");
  content.setAttribute('id',`tab_${platform}`);
  content.setAttribute('role',"tabpanel");
  if(index==0){
    content.classList.add('active');
    content.classList.add('show');
  }
  let acc = document.createElement('div');
  acc.classList.add('accordion')

  releases.forEach((elem,index) => {
    acc.append(render_release(platform,elem));
  });
  content.append(acc);

   return content;
}
function populateTabs(json){
  Object.keys(json).forEach(function (platform,index) {

    $('#platforms_tabs')[0].append(render_platform_tab(platform,index==0?true:false));
    let firmware_content=render_firmware_content(platform,json[platform],index);
    $('#firmware_content')[0].append(firmware_content);

  });
}
function setManifests(json){
  Object.keys(json).forEach(function (platform,index) {
    try {
      const release=json[platform].find(item => item.bits =='16');
      const manifest_link=`artifacts/${release.manifest}`;
      if(platform==="I2S-4MFlash"){
        $('#button_web_install')[0].attributes['manifest'].value = manifest_link;
      }
      $(`#card${platform}_header`).attr('manifest',manifest_link);
    } catch (error) {
      console.error(`Unable to set manifest for platform ${platform}: ${error}`);
    }
  });
}



fetch('./artifacts/manifest')
  .then((response) => response.json())
  .then((resp) => {
    let platforms = {}
    resp.forEach((element) => {
      let platform = `${element.release_details.platform}`
      if (!platforms[platform]) {
        platforms[platform] = []
      }
      platforms[platform].push({ 'branch': element.release_details.branch, 'bits': element.release_details.bitrate, 'version': element.release_details.version, entry: platform + element.release_details.version.replace('.', '_') + '-' + element.release_details.bitrate, 'manifest': element.manifest_name, 'description': element.description })
    })
    //populateTabs(platforms);
    setManifests(platforms);
    

    let cont = ['ci_'];
    let events = ['hide.bs.collapse','shown.bs.collapse'];
    $('a[data-bs-toggle="tab"]').on('shown.bs.tab', function (e) {
      $('#button_web_install')[0].attributes['manifest'].value = $(`#${e.target.href.split('#')[1]}`).find('div[manifest]:first')[0].attributes['manifest'].value;
    })
    
     cont.forEach((v)=>{
       events.forEach((e)=>{
         $(`[id^='${v}']`).on(e, function (evt) {
            $('#button_web_install')[0].attributes['manifest'].value =evt.target.attributes['manifest'].value;

         });
       });

     });
     //$('#platforms_tabs  a[href="#tab_I2S-4MFlash"]')[0].click()
     function unclickRadio() {
      $("input:radio").prop("checked", false);
    }

  // code below pulled from https://write.corbpie.com/bootstrap-cards-as-selectable-radio-buttons/    
    function clickRadio(inputElement) {
        $("#" + inputElement).prop("checked", true);
    }
    function removeActive() {
        $(".card-header").removeClass("active");
        $(".card-header").removeClass("bg-primary")
        $(".card-header").removeClass("text-white")
        
    }
    function makeActive(element) {
      const uielem=$("#" + element + "_header")
      uielem.addClass("active");
      uielem.addClass("bg-primary");
      uielem.addClass("text-white");
      $('#button_web_install')[0].attributes['manifest'].value = uielem[0].attributes['manifest'].value;
      
    }
    $('input:radio').on("change",function () {//Clicking input radio
        let radioClicked = $(this).attr('id');
        unclickRadio();
        removeActive();
        clickRadio(radioClicked);
        makeActive(radioClicked);
    });
    $(".card").on('click',function () {//Clicking the card
        let inputElement = $(this).find('input[type=radio]').attr('id');
        unclickRadio();
        removeActive();
        makeActive(inputElement);
        clickRadio(inputElement);
    });
    
    
    
  });

    

