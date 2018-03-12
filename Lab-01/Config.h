#pragma once

#include <string>

namespace Layout
{
    const std::string WinTitle { "GFK Lab 01" };
    const unsigned WinWidth    { 800u };
    const unsigned WinHeight   { 650u };

    const unsigned RGBScale        { 255u };
    const unsigned RGBScalesAmount { 3u };
    const unsigned ColorsMargin    { 1u };
    const unsigned ColorsWidth     { RGBScale * 3u };
    const unsigned ColorsHeight    { 60u };

    const unsigned ColorsPosX { ColorsMargin };
    const unsigned ColorsPosY { ColorsMargin };

    const unsigned PickMargin { 4u };
    const unsigned PickWidth  { WinWidth - ColorsWidth - ColorsMargin - PickMargin * 2u };
    const unsigned PickHeight { (ColorsHeight - PickMargin * 3u) / 2u };

    const unsigned PickFgPosX { ColorsWidth + ColorsMargin + PickMargin };
    const unsigned PickBgPosX { PickFgPosX };
    const unsigned PickFgPosY { PickMargin };
    const unsigned PickBgPosY { PickFgPosY + PickHeight + PickMargin };

    const unsigned ToolbarMargin    { 5u };
    const unsigned ToolbarCol1Width { 200u };
    const unsigned ToolbarCol2Width { 250u };
    const unsigned ToolbarCol3Width { 200u };
    const unsigned ToolbarRowHeight { 15u };

    const unsigned ToolbarCol1PosX { ToolbarMargin };
    const unsigned ToolbarCol2PosX { ToolbarCol1PosX + ToolbarCol1Width };
    const unsigned ToolbarCol3PosX { ToolbarCol2PosX + ToolbarCol2Width };
    const unsigned ToolbarCol4PosX { ToolbarCol3PosX + ToolbarCol3Width };
    const unsigned ToolbarRow3PosY { WinHeight - ToolbarMargin - ToolbarRowHeight };
    const unsigned ToolbarRow2PosY { ToolbarRow3PosY - ToolbarRowHeight };
    const unsigned ToolbarRow1PosY { ToolbarRow2PosY - ToolbarRowHeight };

    const unsigned WorkspaceMargin { 2u };
    const unsigned WorkspaceWidth  { WinWidth - WorkspaceMargin * 2u };
    const unsigned WorkspaceHeight { WinHeight - ColorsHeight - ColorsMargin
                                     - ToolbarRowHeight * 3u - ToolbarMargin
                                     - WorkspaceMargin * 2u };

    const unsigned WorkspacePosX { WorkspaceMargin };
    const unsigned WorkspacePosY { ColorsHeight + ColorsMargin + WorkspaceMargin };
}
