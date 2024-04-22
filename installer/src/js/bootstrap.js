import * as bootstrap from "bootstrap";
import 'typeface-roboto'

export const initBootstrap = function (config) {
  // Enabling tooltips
  if (config.tooltip) {
    const tooltipTriggerList = [].slice.call(document.querySelectorAll('[data-bs-toggle="tooltip"]'))

    tooltipTriggerList.map(function (tooltipTriggerEl) {
      return new bootstrap.Tooltip(tooltipTriggerEl)
    })
  }

  // Enabling popovers
  if (config.popover) {
    const popoverTriggerList = [].slice.call(document.querySelectorAll('[data-bs-toggle="popover"]'))

    popoverTriggerList.map(function (popoverTriggerEl) {
      return new bootstrap.Popover(popoverTriggerEl, {})
    })
  }

  // Enabling toasts
  if (config.toasts) {
    const toastTriggerList = [].slice.call(document.querySelectorAll('[data-bs-toggle="toast"]'))

    toastTriggerList.map(function (toastTriggerEl) {
      // Define the target property
      let toastTarget = null

      if ("A" === toastTriggerEl.nodeName) {
        toastTarget = toastTriggerEl.href || null

        if (toastTarget.includes('#')) {
          toastTarget = `#${toastTarget.split("#").pop()}`
        } else {
          return
        }
      } else if ("BUTTON" === toastTriggerEl.nodeName) {
        toastTarget = toastTriggerEl.dataset.bsTarget || null
      }

      // Check if the target exists
      const toastTargetEl = document.querySelector(toastTarget);

      if (!toastTargetEl) {
        return
      }

      // Initialize toast
      const toast = new bootstrap.Toast(toastTargetEl, {})
      
      // Add click even to trigger
      toastTriggerEl.addEventListener("click", function (event) {
        event.preventDefault();
        toast.show()
      })
    })
  }
}
