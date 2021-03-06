// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/shell/context_menu.h"

#include "ash/launcher/launcher.h"
#include "ash/root_window_controller.h"
#include "ash/shell.h"
#include "ash/wm/shelf_types.h"
#include "grit/ash_strings.h"
#include "ui/base/l10n/l10n_util.h"

namespace ash {
namespace shell {

ContextMenu::ContextMenu(aura::RootWindow* root)
    : ui::SimpleMenuModel(NULL),
      root_window_(root),
      alignment_menu_(root) {
  DCHECK(root_window_);
  set_delegate(this);
  AddCheckItemWithStringId(MENU_AUTO_HIDE,
                           IDS_AURA_LAUNCHER_CONTEXT_MENU_AUTO_HIDE);
  AddSubMenuWithStringId(MENU_ALIGNMENT_MENU,
                         IDS_AURA_LAUNCHER_CONTEXT_MENU_POSITION,
                         &alignment_menu_);
}

ContextMenu::~ContextMenu() {
}

bool ContextMenu::IsCommandIdChecked(int command_id) const {
  switch (command_id) {
    case MENU_AUTO_HIDE:
      return Shell::GetInstance()->IsShelfAutoHideMenuHideChecked(root_window_);
    default:
      return false;
  }
}

bool ContextMenu::IsCommandIdEnabled(int command_id) const {
  return true;
}

bool ContextMenu::GetAcceleratorForCommandId(
      int command_id,
      ui::Accelerator* accelerator) {
  return false;
}

void ContextMenu::ExecuteCommand(int command_id) {
  switch (static_cast<MenuItem>(command_id)) {
    case MENU_AUTO_HIDE:
      Shell::GetInstance()->SetShelfAutoHideBehavior(
          Shell::GetInstance()->GetToggledShelfAutoHideBehavior(root_window_),
          root_window_);
      break;
    case MENU_ALIGNMENT_MENU:
      break;
  }
}

}  // namespace shell
}  // namespace ash
