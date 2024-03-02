%%扫雷小程序 R2014a
function  varargout = Game_NewClearMine( varargin )
if nargin == 0
    OldHandle = findobj( 'Type', 'figure', 'Tag', 'NewClearMine' ) ;
    if ishandle( OldHandle )
        close( OldHandle ) ;
    end
    FigureHandle = figure('Visible', 'off') ;
    init_FigureContent( FigureHandle ) ;  
elseif ischar( varargin{1} )
    if nargout > 0
        [varargout{1:nargout}] = feval(varargin{:}) ;
    else
        feval(varargin{:}) ;
    end
end
function generate_FigureContent( FigureHandle, ButtonNumber ) ;
TabSpace = 10 ;
MidSpace = 1 ;
ButtonColNumber = ButtonNumber(2) ;
ButtonRowNumber = ButtonNumber(1) ;
TextHeight = 25 ;
FigureWidth = ButtonColNumber * (21 + MidSpace) + TabSpace * 4 ;
FigureHeight = ButtonRowNumber * (21 + MidSpace) + TabSpace * 5 + TextHeight ;
set( FigureHandle, 'Position', [100, 100, FigureWidth, FigureHeight], 'Menubar', 'none',...
    'Visible', 'off', 'Name', '扫雷',  'Tag', 'NewClearMine', 'NumberTitle', 'off',...
    'DoubleBuffer', 'on', 'Units', 'pixel', 'Color', [0.85 0.85 0.85], 'Resize', 'off',...
    'KeyPressFcn', 'Game_NewClearMine(''Keypress_fcn'', gcbf)' ) ;
AxesHandle = axes( 'Position', [0, 0, 1, 1], 'Units', 'pixel', 'Tag', 'MainAxes',...
    'XLim', [0, FigureWidth], 'YLim', [0, FigureHeight], 'Visible', 'off' ) ;
LineXArray = [TabSpace, FigureWidth-TabSpace, FigureWidth-TabSpace, TabSpace, TabSpace] ;
LineYArray = [TabSpace, TabSpace, FigureHeight-TabSpace, FigureHeight-TabSpace, TabSpace] ;
line( LineXArray, LineYArray, 'Color', 'k' , 'Tag', 'MainFrame') ;
MenuHandle = uimenu( FigureHandle, 'Label', '游戏', 'Tag', 'MainMenu' ) ;
SubMenuTag = {'Begin', 'Easy', 'Normal', 'Hard', 'Custom', 'Exit' } ;
SubMenuString = {'开始(&B)', '低级(&E)', '中级(&N)', '高级(&H)', '自定义(&C)', '退出(&Q)'};
SubMenuCallback = {'Game_NewClearMine( ''BeginMenu_Callback'', gcbo)',...
        'Game_NewClearMine( ''EasyMenu_Callback'', gcbo)',...
        'Game_NewClearMine( ''NormalMenu_Callback'', gcbo)',...
        'Game_NewClearMine( ''HardMenu_Callback'', gcbo)' ,...
        'Game_NewClearMine( ''CustomMenu_Callback'', gcbo)',...
        'close(gcf)'} ;
SubMenuSeparator = {'off', 'on', 'off','off','off','on'} ;

for num = 1: length( SubMenuTag )
    SubMenuHandle(num) = uimenu( MenuHandle ) ;
    set( SubMenuHandle(num), 'Tag', SubMenuTag{num},...
        'Label', SubMenuString{num},...
        'Separator', SubMenuSeparator{num},...
        'Callback', SubMenuCallback{num} ) ;
end

MenuHandle = uimenu( FigureHandle, 'Label', '帮助', 'Tag', 'MenuHelp' ) ;
uimenu( MenuHandle, 'Label', '帮助', 'Tag', 'Help',...
    'Callback', 'helpdlg(''游戏开始（至少点开一个格子）后，按Ctrl+Enter可以直接过关。'', ''最终秘技'')' ) ;


if ButtonColNumber < 8
    TextWidth = (FigureWidth - TabSpace * 2 - TabSpace * 2 - TabSpace * 2 * 2) / 3 ;
else
    TextWidth = (FigureWidth - TabSpace * 2 - TabSpace * 2 - TabSpace * 4 * 2) / 3 ;
end
TextPosition = [TabSpace*2 FigureHeight-2*TabSpace-TextHeight TextWidth TextHeight] ;

if ButtonColNumber < 8
    TextFontSize = 12 ;
else
    TextFontSize = 16 ;
end

TextTag = {'MineNumber', 'Face', 'Time'} ;
TextString = {'', '', '0'} ;
TextStyle = {'text', 'pushbutton', 'text'} ;
TextCallback = {'', 'Game_NewClearMine(''BeginMenu_Callback'', gcbo)', ''} ;
for num = 1: length(TextTag)
    TempTextPosition = TextPosition ;
    if ButtonColNumber < 8
        TempTextPosition(1) = TempTextPosition(1) + (num-1) * (TextWidth + 2 * TabSpace) ;
    else
        TempTextPosition(1) = TempTextPosition(1) + (num-1) * (TextWidth + 4 * TabSpace) ;
    end    
    UicontrolHandle = uicontrol( 'Style', TextStyle{num}, 'Position', TempTextPosition, 'Tag', TextTag{num},...
        'BackgroundColor', [0.7 0.7 0.7], 'FontSize', TextFontSize, 'HorizontalAlignment', 'center',...
        'String', TextString{num}, 'Callback', TextCallback{num} ) ; 
    if num == 2
        TempTextPosition(1) = TempTextPosition(1) + (TempTextPosition(3) - 23) / 2 ;
        TempTextPosition(3) = 23 ;
        set( UicontrolHandle, 'Position', TempTextPosition) ;
    end
end

ButtonXPos = TabSpace * 2 ;
ButtonWidth =  21 ;
ButtonHeight = 21 ;
ButtonYPos = TabSpace * 3 + ButtonHeight * ButtonRowNumber ;
ButtonPosition = [ButtonXPos ButtonYPos ButtonWidth ButtonHeight] ;

setappdata( FigureHandle, 'ButtonPosition', ButtonPosition ) ;
setappdata( FigureHandle, 'ButtonWidth', 21 + MidSpace ) ;

if ButtonColNumber == 16
    x = (0: ButtonColNumber) * (21 + MidSpace) + ButtonXPos - 1 ;
else
    x = (0: ButtonColNumber) * (21 + MidSpace) + ButtonXPos - 2 ;
end
y = (-ButtonRowNumber:0) * (21 + MidSpace) + ButtonYPos - 1 ;

[X, Y] = meshgrid(x, y) ;

LineRowNum = ButtonRowNumber + 1 ;
LineColNum = ButtonColNumber + 1 ;

vert = [X(:), Y(:)] ;
AreaMatrix = repmat( [1 2 2+LineRowNum 1+LineRowNum 1], LineRowNum - 1, 1 ) ;
LineAreaMatrix = AreaMatrix + repmat((LineRowNum-2:-1:0)', 1, size(AreaMatrix, 2)) ;
LineAreaMatrix = repmat(LineAreaMatrix, LineColNum - 1, 1) ;
AreaMatrix = repmat((0:LineColNum-2)*LineRowNum,(LineRowNum - 1)*5, 1) ;  
AreaMatrix = AreaMatrix(:) ;
AreaMatrix = reshape(AreaMatrix, 5, []) ;
fac = LineAreaMatrix + AreaMatrix' ;
tcolor = ones(size(fac,1),3) * 0.75 ;

patch( 'Faces', fac, 'Vertices', vert,'FaceVertexCData', tcolor, 'FaceColor','flat', 'Tag', 'MainPatch',...
    'ButtonDownFcn', 'Game_NewClearMine( ''ButtonDown_Callback'', gcbo )' )


% ------------------------------------------------------------------------
function init_FigureContent( FigureHandle ) ;

handles = guidata( FigureHandle ) ;

GameInfo = getappdata( FigureHandle, 'GameInfo' ) ;

if isempty( GameInfo )
    GameInfo.RowNumber = 9 ;
    GameInfo.ColNumber = 9 ;
    GameInfo.MineNumber = 10 ;    
end

ButtonNumber = [GameInfo.RowNumber GameInfo.ColNumber] ;
close(FigureHandle) ;
FigureHandle = figure('Visible', 'off') ;
generate_FigureContent( FigureHandle, ButtonNumber ) ;

setappdata( FigureHandle, 'GameInfo', GameInfo ) ;

movegui( FigureHandle, 'center' ) ;
set( FigureHandle, 'Visible', 'on' ) ;

handles = guihandles( FigureHandle ) ;
guidata( FigureHandle, handles) ;    

set( handles.MineNumber, 'String', num2str(GameInfo.MineNumber) ) ;

BeginMenu_Callback( FigureHandle ) ;


% -------------------------------------------------------------------------
function BeginMenu_Callback( h )

handles = guidata( h ) ;

setappdata( handles.NewClearMine, 'GameIsBegin', 0 ) ;
setappdata( handles.NewClearMine, 'GameOver', 1 ) ;
setappdata( handles.NewClearMine, 'CountSecond', 1 ) ;
setappdata( handles.NewClearMine, 'MineNumberArray', [] ) ;

Matrix = com_GetFaceImage( 'Smile' ) ;
set( handles.Face, 'CData', Matrix/255 ) ;

GameInfo = getappdata( handles.NewClearMine, 'GameInfo' ) ;
set( handles.MineNumber, 'String', num2str(GameInfo.MineNumber) ) ;

cla( [handles.MainPatch, handles.MainFrame] ) ;

CData = get( handles.MainPatch, 'FaceVertexCData' ) ;
CData(:,:) = 0.75 ;
set( handles.MainPatch, 'FaceVertexCData', CData ) ;

setappdata( handles.NewClearMine, 'TextHandle', [] ) ;


% ------------------------------------------------------------------------
function  EasyMenu_Callback( h ) 

handles = guidata( h ) ;

GameInfo.RowNumber = 9 ;
GameInfo.ColNumber = 9 ;
GameInfo.MineNumber = 10 ; 
setappdata( handles.NewClearMine, 'GameInfo', GameInfo ) ;

init_FigureContent( handles.NewClearMine ) ;


% ------------------------------------------------------------------------
function  NormalMenu_Callback( h ) 

handles = guidata( h ) ;

GameInfo.RowNumber = 16 ;
GameInfo.ColNumber = 16 ;
GameInfo.MineNumber = 40 ; 
setappdata( handles.NewClearMine, 'GameInfo', GameInfo ) ;

init_FigureContent( handles.NewClearMine ) ;


% ------------------------------------------------------------------------
function  HardMenu_Callback( h ) 

handles = guidata( h ) ;

GameInfo.RowNumber = 16 ;
GameInfo.ColNumber = 30 ;
GameInfo.MineNumber = 99 ; 
setappdata( handles.NewClearMine, 'GameInfo', GameInfo ) ;

init_FigureContent( handles.NewClearMine ) ;


% -------------------------------------------------------------------------
function  ButtonDown_Callback( h )

handles = guidata( h ) ;

CurrentPoint = get( handles.NewClearMine, 'CurrentPoint' ) ;

GameInfo = getappdata( handles.NewClearMine, 'GameInfo' ) ;
RowNumber = GameInfo.RowNumber ;
ColNumber = GameInfo.ColNumber ;
TotalMineNumber = GameInfo.MineNumber ;
    
ButtonPosition = getappdata( handles.NewClearMine, 'ButtonPosition' ) ;
ButtonWidth = getappdata( handles.NewClearMine, 'ButtonWidth' ) ;

XPos = ButtonPosition(1) ;
YPos = ButtonPosition(2) ;

XIndex = floor( (CurrentPoint(1) - XPos) / ButtonWidth ) ;
YIndex = floor( (YPos - CurrentPoint(2)+ButtonWidth) / ButtonWidth ) ;
ButtonIndex = XIndex * RowNumber + YIndex ;

if strcmp( get(handles.NewClearMine, 'SelectionType' ), 'alt' ) 
    RightButtonDown_Callback( h, ButtonIndex, XPos, YPos, XIndex, YIndex, ButtonWidth ) ;
    return ;
elseif strcmp( get(handles.NewClearMine, 'SelectionType' ), 'open' ) 
    return ;
end

TextHandle = getappdata( handles.NewClearMine, 'TextHandle' ) ;
if ~isempty(TextHandle)
    TextIndex = get( TextHandle, 'UserData' ) ;
    if iscell(TextIndex)
        TextIndex = [TextIndex{:}] ;
    end
    if  ismember(ButtonIndex, TextIndex)
        return 
    end
end

GameIsBegin = getappdata( handles.NewClearMine, 'GameIsBegin' ) ;

if isempty( GameIsBegin )
    GameIsBegin = 0 ;    
end

if GameIsBegin == 0
    setappdata( handles.NewClearMine, 'GameOver', 0 ) ;    
    InitMineSetting( h, RowNumber, ColNumber, TotalMineNumber, ButtonIndex ) ;
else
    GameOver = getappdata( handles.NewClearMine, 'GameOver' ) ;
    if isempty(GameOver) | GameOver == 1
        return ;
    end 
end

MineNumberArray = getappdata( handles.NewClearMine, 'MineNumberArray' ) ;
SolveArray = getappdata( handles.NewClearMine, 'SolveArray' ) ;

MineNumber = MineNumberArray(ButtonIndex) ;

CData = get( handles.MainPatch, 'FaceVertexCData' ) ;
if  isnan( MineNumber ) 
    UsefulIndex = getappdata( handles.NewClearMine, 'UsefulIndex' ) ;
    for num = 1: length(UsefulIndex)
        TempIndex = UsefulIndex(num) ;
        XIndex = ceil(TempIndex/RowNumber)-1 ;
        YIndex = mod((TempIndex-1), RowNumber)+1 ;
        TextXPos = (XIndex + 0.5) * ButtonWidth + XPos ;
        TextYPos = YPos - (YIndex + 0.5) * ButtonWidth + ButtonWidth ;
        text( TextXPos, TextYPos, '●',  'Parent', handles.MainAxes, 'HorizontalAlignment', 'center', 'FontSize',13  ) ;
    end    
    
    if ~isempty(TextHandle)
        delete(TextHandle) ;
        setappdata( handles.NewClearMine, 'TextHandle', [] ) ;
    end
    Matrix = com_GetFaceImage( 'Cry' ) ;
    set( handles.Face, 'CData', Matrix/255 ) ;

    setappdata( handles.NewClearMine, 'GameOver', 1 ) ;    
elseif MineNumber == 0    
    SafeIndex = getappdata( handles.NewClearMine, 'SafeIndex' ) ;   
    UnionIndex = getappdata( handles.NewClearMine, 'UnionIndex' ) ;
    
    Index = find(SafeIndex == ButtonIndex ) ;
    UnionID = UnionIndex(Index) ;
    
    TempUnionIndex = find(UnionIndex == UnionID) ;
    ClearIndex = SafeIndex(TempUnionIndex) ;
    
%     ButtonHandles = getappdata( handles.NewClearMine, 'ButtonHandles' ) ;
%     set( ButtonHandles(ClearIndex), 'String', '', 'Style', 'text', 'BackgroundColor', [0.85 0.85 0.85]) ;
    CData(ClearIndex,:) = repmat([0.85 0.85 0.85], length(ClearIndex), 1) ;
%     set( handles.MainPatch, 'FaceVertexCData', CData  ) ;
    
    SolveArray = setdiff(SolveArray, ClearIndex) ;
    
    GameInfo = getappdata( handles.NewClearMine, 'GameInfo' ) ;
    RowNumber = GameInfo.RowNumber ;
    ColNumber = GameInfo.ColNumber ;
    AroundArray = zeros(length(ClearIndex)*8,1) ;
    for num = 1: length(ClearIndex)
        TempIndex = ClearIndex(num) ;
        if mod( TempIndex, RowNumber) == 1
            AroundIndex = TempIndex + [1 -RowNumber -RowNumber+1 RowNumber RowNumber+1] ;
        elseif mod( TempIndex, RowNumber) == 0
            AroundIndex = TempIndex + [-1 -RowNumber -RowNumber-1 RowNumber RowNumber-1] ;
        else
            AroundIndex = TempIndex + [-1 1 -RowNumber -RowNumber-1 -RowNumber+1 RowNumber-1 RowNumber RowNumber+1] ;
        end
        AroundIndex(AroundIndex<=0|AroundIndex>RowNumber*ColNumber) = [] ;
        AroundArray((num-1)*8+1:(num-1)*8+length(AroundIndex)) = AroundIndex ;
    end
    AroundArray(AroundArray==0) = [] ;
    AroundArray = unique(AroundArray) ;
    
    MineNumber = MineNumberArray(AroundArray) ;
    ColorArray = [0 0 1;0 1 0;1 0 0;0 1 1;1 0 1;1 1 0;0 0 0;0 0 1;1 1 0] ;
    for num = 1: max(max(MineNumber))
        TempIndex = find(MineNumber == num) ;
        if ~isempty(TempIndex)  
            CData(AroundArray(TempIndex),:) = repmat([0.85 0.85 0.85],length(TempIndex),1) ;
        end
    end
    set( handles.MainPatch, 'FaceVertexCData', CData  ) ;    
    for num = 1: numel(MineNumber)
        TempMineNumber = MineNumber(num) ;        
        if TempMineNumber~=0
            TempIndex = AroundArray(num) ;
            XIndex = ceil(TempIndex/RowNumber)-1 ;
            YIndex = mod((TempIndex-1), RowNumber)+1 ;
            TextXPos = (XIndex + 0.5) * ButtonWidth + XPos ;
            TextYPos = YPos - (YIndex + 0.5) * ButtonWidth + ButtonWidth ;
            text( TextXPos, TextYPos, num2str(TempMineNumber), 'Color', ColorArray(TempMineNumber,:),...
                'Parent', handles.MainAxes, 'HorizontalAlignment', 'center', 'FontSize',13 ) ;
        end
    end
    
    SolveArray = setdiff(SolveArray, AroundArray) ;
    
    if isempty(SolveArray)
        setappdata( handles.NewClearMine, 'GameOver', 1 ) ;
        helpdlg('完成了，恭喜!') ;
    else
        setappdata( handles.NewClearMine, 'SolveArray', SolveArray ) ;
    end
else 
    ColorArray = [0 0 1;0 1 0;1 0 0;0 1 1;1 0 1;1 1 0;0 0 0;0 0 1;1 1 0] ;
    CData(ButtonIndex,:) = [0.85 0.85 0.85] ;
    set( handles.MainPatch, 'FaceVertexCData', CData  ) ;
    TextXPos = (XIndex + 0.5) * ButtonWidth + XPos ;
    TextYPos = YPos - (YIndex + 0.5) * ButtonWidth + ButtonWidth ;
    text( TextXPos, TextYPos, num2str(MineNumber), 'Color', ColorArray(MineNumber,:),...
        'Parent', handles.MainAxes, 'HorizontalAlignment', 'center', 'FontSize',13  ) ;
    SolveArray(SolveArray == ButtonIndex) = [] ;
    if isempty(SolveArray)
        setappdata( handles.NewClearMine, 'GameOver', 1 ) ;
        helpdlg('完成了，恭喜!') ;
    else
        setappdata( handles.NewClearMine, 'SolveArray', SolveArray ) ;
    end
end

if GameIsBegin == 0
    GameIsBegin = 1 ;
    setappdata( handles.NewClearMine, 'GameIsBegin', GameIsBegin ) ;
    BeginCalculate_Callback( h ) ;
end


% --------------------------------------------------------------------
function RightButtonDown_Callback( h, ButtonIndex, XPos, YPos, XIndex, YIndex, ButtonWidth ) ;

handles = guidata( h ) ;

if strcmp( get(handles.NewClearMine, 'SelectionType' ), 'alt' )
    GameIsBegin = getappdata( handles.NewClearMine, 'GameIsBegin' ) ;
    GameOver = getappdata( handles.NewClearMine, 'GameOver' ) ;
    if isempty(GameIsBegin) | GameIsBegin == 0
        return ;
    end
    if isempty(GameOver) | GameOver == 1
        return ;
    end    
    
    CData = get( handles.MainPatch, 'FaceVertexCData' ) ;
    if ~isequal( CData(ButtonIndex,:),[0.75, 0.75, 0.75])
        return;
    end
    
    MineNumber = str2num( get( handles.MineNumber, 'String' ) ) ;    
    if isempty( MineNumber) | MineNumber <= 0 
        return ;
    end  
    
    TextXPos = (XIndex + 0.5) * ButtonWidth + XPos ;
    TextYPos = YPos - (YIndex + 0.5) * ButtonWidth + ButtonWidth ;
        
    TextHandle = getappdata( handles.NewClearMine, 'TextHandle' ) ;    
    Index = [] ;  
    if ~isempty(TextHandle)
        TextIndex = get( TextHandle, 'UserData' ) ;
        if iscell(TextIndex)
            TextIndex = [TextIndex{:}] ;
        end
        Index = find(TextIndex == ButtonIndex) ;
    end
    if isempty(Index)
        set( handles.MineNumber, 'String', num2str(MineNumber-1) ) ;
        
        NewTextHandle = text( TextXPos, TextYPos, '▲', 'Color', 'r','UserData', ButtonIndex,...
            'Parent', handles.MainAxes, 'HorizontalAlignment', 'center', 'FontSize',13, 'Hittest', 'off'  ) ;
        setappdata( handles.NewClearMine, 'TextHandle', [TextHandle; NewTextHandle] ) ;
    else
        set( handles.MineNumber, 'String', num2str(MineNumber+1) ) ;
        delete(TextHandle(Index)) ;
        TextHandle(Index) = [] ;
        setappdata( handles.NewClearMine, 'TextHandle', TextHandle ) ;
    end
end


% ------------------------------------------------------------------------
function InitMineSetting( h, RowNumber, ColNumber, TotalMineNumber, ButtonIndex )

handles = guidata( h ) ;

% 随机取格子布雷
RandIndex = randperm( RowNumber*ColNumber ) ;
UsefulIndex = RandIndex(1:TotalMineNumber) ;

if  any( UsefulIndex == ButtonIndex ) % 比ismember( ButtonIndex, UsefulIndex )效率高一点 
    % 选的第一个格子不能有雷
    UsefulIndex = RandIndex(1: TotalMineNumber+1) ;
    UsefulIndex(UsefulIndex == ButtonIndex) = [] ;
end
setappdata( handles.NewClearMine, 'UsefulIndex', UsefulIndex ) ;

% 定义保存雷数目的向量
MineNumberArray = zeros(RowNumber,ColNumber) ;
% 布了雷的格子的雷数值设为nan或inf
MineNumberArray(UsefulIndex) = nan ;

% 对雷格四周的格子雷数值各+1
for num = 1: TotalMineNumber    
    TempIndex = UsefulIndex(num) ;
    % 周围格子的序号，可以包括自身，因为nan+1 = nan
    if mod(TempIndex, RowNumber) == 0
        AroundIndex = [-1 -1 -1; 0 0 0] + repmat( [-1:1]*RowNumber+TempIndex, 2, 1) ;
    elseif mod(TempIndex, RowNumber) == 1
        AroundIndex = [0 0 0; 1 1 1] + repmat( [-1:1]*RowNumber+TempIndex, 2, 1) ;
    else
        AroundIndex = [-1 -1 -1; 0 0 0; 1 1 1] + repmat( [-1:1]*RowNumber+TempIndex, 3, 1) ;
    end
    AroundIndex(AroundIndex<=0 | AroundIndex>RowNumber*ColNumber) = [] ;
    MineNumberArray(AroundIndex) = MineNumberArray(AroundIndex) + 1 ;
end
setappdata( handles.NewClearMine, 'MineNumberArray', MineNumberArray ) ;

MineNumberArray = MineNumberArray(:) ;
% 对周围无雷（即值还是0）的点进行分组
SafeIndex = find(MineNumberArray == 0) ;
UnionIndex = ones( size(MineNumberArray) ) * inf;
UnionIndex(SafeIndex) = 0 ;
NotSureNumber = 0 ;
TempMaxUnion = 0 ;
NextNotSureIndex = 0 ;

while(any(UnionIndex<=0))    
    if NotSureNumber > 0
        if NextNotSureIndex ~= 0
            TempNotSureIndex = NextNotSureIndex ;
            if mod( TempNotSureIndex, RowNumber) == 1
                AroundIndex = TempNotSureIndex + [1 -RowNumber -RowNumber+1 RowNumber RowNumber+1] ;
            elseif mod( TempNotSureIndex, RowNumber) == 0
                AroundIndex = TempNotSureIndex + [-1 -RowNumber -RowNumber-1 RowNumber RowNumber-1] ;
            else
                AroundIndex = TempNotSureIndex + [-1 1 -RowNumber -RowNumber-1 -RowNumber+1 RowNumber-1 RowNumber RowNumber+1] ;
            end           
            AroundIndex(AroundIndex<=0 | AroundIndex>RowNumber*ColNumber) = [] ;
            if ~isempty(AroundIndex)
                RealNotSureIndex = find(UnionIndex(AroundIndex) == 0) ;
                AroundIndex = AroundIndex(RealNotSureIndex) ;
            end
            UnionIndex(TempNotSureIndex) = TempMaxUnion ;
            NotSureNumber = NotSureNumber - 1 ;
            NextNotSureIndex = 0 ;
            if ~isempty(AroundIndex)   
                UnionIndex(AroundIndex) = -1 ;
                NextNotSureIndex = AroundIndex(1) ;
                NotSureNumber = NotSureNumber + length(AroundIndex) ;
            end
        else
            for num = 1: length(SafeIndex)
                TempNotSureIndex = UnionIndex(SafeIndex(num)) ;
                if TempNotSureIndex == -1                    
                    if mod( SafeIndex(num), RowNumber) == 1
                        AroundIndex = SafeIndex(num) + [1 -RowNumber -RowNumber+1 RowNumber RowNumber+1] ;
                    elseif mod( SafeIndex(num), RowNumber) == 0
                        AroundIndex = SafeIndex(num) + [-1 -RowNumber -RowNumber-1 RowNumber RowNumber-1] ;
                    else
                        AroundIndex = SafeIndex(num) + [-1 1 -RowNumber -RowNumber-1 -RowNumber+1 RowNumber-1 RowNumber RowNumber+1] ;
                    end 
                    AroundIndex(AroundIndex<=0 | AroundIndex>RowNumber*ColNumber) = [] ;
                    if ~isempty(AroundIndex)
                        RealNotSureIndex = find(UnionIndex(AroundIndex) == 0) ;
                        AroundIndex = AroundIndex(RealNotSureIndex) ;
                    end
                    UnionIndex(SafeIndex(num)) = TempMaxUnion ;
                    NotSureNumber = NotSureNumber - 1 ;
                    NextNotSureIndex = 0 ;
                    if ~isempty(AroundIndex)                    
                        UnionIndex(AroundIndex) = -1 ;
                        NextNotSureIndex = AroundIndex(1) ;
                        NotSureNumber = NotSureNumber + length(AroundIndex) ;
                    end
                    break;
                end
            end
        end
    else 
        for num = 1: length( SafeIndex )
            TempIndex = SafeIndex(num) ;
            if UnionIndex(TempIndex) == 0
                if mod( TempIndex, RowNumber) == 1
                    AroundIndex = TempIndex + [1 -RowNumber -RowNumber+1 RowNumber RowNumber+1] ;
                elseif mod( TempIndex, RowNumber) == 0
                    AroundIndex = TempIndex + [-1 -RowNumber -RowNumber-1 RowNumber RowNumber-1] ;
                else
                    AroundIndex = TempIndex + [-1 1 -RowNumber -RowNumber-1 -RowNumber+1 RowNumber-1 RowNumber RowNumber+1] ;
                end
                AroundIndex(AroundIndex<=0 | AroundIndex>RowNumber*ColNumber) = [] ;
                if ~isempty(AroundIndex)
                    RealNotSureIndex = find(UnionIndex(AroundIndex) <= 0) ;
                    AroundIndex = AroundIndex(RealNotSureIndex) ;
                end
                TempMaxUnion = TempMaxUnion + 1 ;
                UnionIndex(TempIndex) = TempMaxUnion ;
                NextNotSureIndex = 0 ;
                if  ~isempty(AroundIndex)   
                    UnionIndex(AroundIndex) = -1 ;
                    NextNotSureIndex = AroundIndex(1) ;
                    NotSureNumber = NotSureNumber + length(AroundIndex) ;
                end
                break;
            end
        end
    end
end
UnionIndex = UnionIndex( ~isinf(UnionIndex) ) ;
setappdata( handles.NewClearMine, 'SafeIndex', SafeIndex ) ;
setappdata( handles.NewClearMine, 'UnionIndex', UnionIndex ) ;

% 保存剩余非雷格子序号
SolveArray = 1: numel(MineNumberArray) ;
SolveArray = setdiff(SolveArray, UsefulIndex) ;
setappdata( handles.NewClearMine, 'SolveArray', SolveArray ) ;



% -----------------------------------------------------------------------
function BeginCalculate_Callback( h ) 

handles = guidata( h ) ;

CountSecond = getappdata( handles.NewClearMine, 'CountSecond' ) ;
if isempty(CountSecond)
    CountSecond = 0 ;
end
while(1)    
    PassTime = sprintf('%d',ceil(CountSecond)) ;
    pause(1) ;
    if ishandle( handles.Time )
        GameOver = getappdata( handles.NewClearMine, 'GameOver' ) ;
        if isempty(GameOver)
            setappdata( handles.NewClearMine, 'GameOver', 0 ) ;
        end
        if GameOver == 1
            break ;
        end
        CountSecond = CountSecond + 1 ;
        set( handles.Time, 'String', PassTime ) ;        
        setappdata( handles.NewClearMine, 'CountSecond', CountSecond ) ;
    else
        break
    end    
end



% -------------------------------------------------------------------------
function CustomMenu_Callback( h )

handles = guidata( h ) ;

GameInfo = getappdata( handles.NewClearMine, 'GameInfo' ) ;

if isempty(GameInfo)
    GameInfo.RowNumber = 10 ;
    GameInfo.ColNumber = 10 ;
    GameInfo.MineNumber = 10 ;
end

RowNumber = GameInfo.RowNumber ;
ColNumber = GameInfo.ColNumber ;
MineNumber = GameInfo.MineNumber ;

FigureHandle = figure( 'Name', '自定义雷区', 'Menubar', 'none', 'WindowStyle', 'modal',...
    'NumberTitle', 'off', 'Position', [300 300 130 100], 'Resize', 'off', 'Visible', 'off' );

setappdata( FigureHandle, 'PassHandle', handles.NewClearMine ) ;

uicontrol( 'sty', 'text', 'str', '高度', 'pos', [10 70 30 20] ) ;
uicontrol( 'sty', 'text', 'str', '宽度', 'pos', [10 40 30 20] ) ;
uicontrol( 'sty', 'text', 'str', '雷数', 'pos', [10 10 30 20] ) ;
uicontrol( 'sty', 'edit', 'tag', 'height', 'str', num2str(RowNumber), 'pos', [50 70 30 20] ) ;
uicontrol( 'sty', 'edit', 'tag', 'width', 'str', num2str(ColNumber), 'pos', [50 40 30 20] ) ;
uicontrol( 'sty', 'edit', 'tag', 'number', 'str', num2str(MineNumber), 'pos', [50 10 30 20] ) ;
uicontrol( 'str', '确定', 'pos', [90 70 30 20],...
    'cal', ['RowNumber = str2num(get(findobj(''tag'', ''height''), ''str''));',...
        'ColNumber = str2num(get(findobj(''tag'', ''width''), ''str''));',...
        'MineNumber = str2num(get(findobj(''tag'', ''number''), ''str''));',...
        '[Msg, status] = Game_NewClearMine( ''CheckDefineValid'', RowNumber, ColNumber, MineNumber);',...
        'if status==0,warndlg(Msg),return,end;',...
        'PassHandle = getappdata( gcf, ''PassHandle'' );',...
        'GameInfo.RowNumber=RowNumber;GameInfo.ColNumber=ColNumber;GameInfo.MineNumber=MineNumber;',...
        'setappdata( PassHandle, ''GameInfo'', GameInfo);',...   
        'close(gcf);',...
        'Game_NewClearMine( ''init_FigureContent'', PassHandle );'] ) ;
uicontrol( 'str', '取消', 'pos', [90 10 30 20], 'cal', 'close(gcf)' ) ;

movegui( FigureHandle, 'center' ) ;
set( FigureHandle, 'Visible', 'on' ) ;




% -------------------------------------------------------------------------
function  [Msg, status] = CheckDefineValid( RowNumber, ColNumber, MineNumber) 

status = 0 ;
Msg = '' ;
if isempty(RowNumber) | RowNumber <= 0 | length(RowNumber) > 1
    Msg = '无效的高度' ;
    return 
end

if isempty(ColNumber) | ColNumber <= 0 | length(ColNumber) > 1
    Msg = '无效的宽度' ;
    return 
end

if isempty(MineNumber) | MineNumber <= 0 | length(MineNumber) > 1 
    Msg = '无效的雷数' ;
    return 
end

if  RowNumber < 5 |  RowNumber > 20
    Msg = '高度必须在5到20间' ;
    return 
end

if  ColNumber < 5 |  ColNumber > 40 
    Msg = '宽度必须在5到40间' ;
    return 
end

if  MineNumber >= ColNumber*RowNumber
    Msg = '雷数大于等于格子总数' ;
    return 
end

status = 1 ;


% -------------------------------------------------------------------------
function Matrix = com_GetMineImage

Matrix = ones(21,21) * 0.75 ;
Matrix(6:15,6:15) = 0 ;
Matrix([5,16],8:13) = 0 ;
Matrix(8:13,[5,16]) = 0 ;
Matrix([4,17],10:11) = 0 ;
Matrix([10,11],4:17) = 0 ;
Matrix = repmat( Matrix, [1,1,3] ) ;


% -------------------------------------------------------------------------
function Matrix = com_GetFlagImage

Matrix = ones(21,21) * 0.75 ;
Matrix(4:18,9:10) = 1  ;
Matrix([5,9],11) = 1 ;
Matrix([6,8],[11:13]) = 1 ;
Matrix(7,10:15) = 1 ;

Matrix2 = Matrix ;
Matrix2(Matrix2 == 1) = 0 ;

Matrix(:,:,2) = Matrix2 ;
Matrix(:,:,3) = Matrix2 ;


% -------------------------------------------------------------------------
function Matrix = com_GetFaceImage( Type )

if strcmp( Type, 'Smile' )
    Matrix(:,:,1) = [[
            255   255   255   255   255   255   255   255   255   255   255   255   255
            255   255   255   255   255   255   255   255   255   255   255   255   255
            255   255   192   192   192   192   192   192   192   192   192   192   192
            255   255   192   192   192   192   192   192   192   192   192   192   192
            255   255   192   192   192   192   192   192   192   192     0     0     0
            255   255   192   192   192   192   192   192     0     0   255   255   255
            255   255   192   192   192   192   192     0   255   255   255   255   255
            255   255   192   192   192   192     0   255   255   255   255   255   255
            255   255   192   192   192     0   255   255   255   255   255   255   255
            255   255   192   192   192     0   255   255   255     0     0   255   255
            255   255   192   192     0   255   255   255   255     0     0   255   255
            255   255   192   192     0   255   255   255   255   255   255   255   255
            255   255   192   192     0   255   255   255   255   255   255   255   255
            255   255   192   192     0   255   255   255   255   255   255   255   255
            255   255   192   192     0   255   255   255     0   255   255   255   255
            255   255   192   192   192     0   255   255   255     0   255   255   255
            255   255   192   192   192     0   255   255   255   255     0     0     0
            255   255   192   192   192   192     0   255   255   255   255   255   255
            255   255   192   192   192   192   192     0   255   255   255   255   255
            255   255   192   192   192   192   192   192     0     0   255   255   255
            255   255   192   192   192   192   192   192   192   192     0     0     0
            255   255   192   192   192   192   192   192   192   192   192   192   192
            255   192   128   128   128   128   128   128   128   128   128   128   128
        ],  [
            255   255   255   255   255   255   255   255   255   255
            255   255   255   255   255   255   255   255   255   192
            192   192   192   192   192   192   192   192   192   128
            192   192   192   192   192   192   192   192   192   128
            0     0   192   192   192   192   192   192   192   128
            255   255     0     0   192   192   192   192   192   128
            255   255   255   255     0   192   192   192   192   128
            255   255   255   255   255     0   192   192   192   128
            255   255   255   255   255   255     0   192   192   128
            255     0     0   255   255   255     0   192   192   128
            255     0     0   255   255   255   255     0   192   128
            255   255   255   255   255   255   255     0   192   128
            255   255   255   255   255   255   255     0   192   128
            255   255   255   255   255   255   255     0   192   128
            255   255   255     0   255   255   255     0   192   128
            255   255     0   255   255   255     0   192   192   128
            0     0   255   255   255   255     0   192   192   128
            255   255   255   255   255     0   192   192   192   128
            255   255   255   255     0   192   192   192   192   128
            255   255     0     0   192   192   192   192   192   128
            0     0   192   192   192   192   192   192   192   128
            192   192   192   192   192   192   192   192   192   128
            128   128   128   128   128   128   128   128   128   128]];
    
    Matrix(:,:,2) = [[
            255   255   255   255   255   255   255   255   255   255   255   255   255
            255   255   255   255   255   255   255   255   255   255   255   255   255
            255   255   192   192   192   192   192   192   192   192   192   192   192
            255   255   192   192   192   192   192   192   192   192   192   192   192
            255   255   192   192   192   192   192   192   192   192     0     0     0
            255   255   192   192   192   192   192   192     0     0   255   255   255
            255   255   192   192   192   192   192     0   255   255   255   255   255
            255   255   192   192   192   192     0   255   255   255   255   255   255
            255   255   192   192   192     0   255   255   255   255   255   255   255
            255   255   192   192   192     0   255   255   255     0     0   255   255
            255   255   192   192     0   255   255   255   255     0     0   255   255
            255   255   192   192     0   255   255   255   255   255   255   255   255
            255   255   192   192     0   255   255   255   255   255   255   255   255
            255   255   192   192     0   255   255   255   255   255   255   255   255
            255   255   192   192     0   255   255   255     0   255   255   255   255
            255   255   192   192   192     0   255   255   255     0   255   255   255
            255   255   192   192   192     0   255   255   255   255     0     0     0
            255   255   192   192   192   192     0   255   255   255   255   255   255
            255   255   192   192   192   192   192     0   255   255   255   255   255
            255   255   192   192   192   192   192   192     0     0   255   255   255
            255   255   192   192   192   192   192   192   192   192     0     0     0
            255   255   192   192   192   192   192   192   192   192   192   192   192
            255   192   128   128   128   128   128   128   128   128   128   128   128
        ],[
            255   255   255   255   255   255   255   255   255   255
            255   255   255   255   255   255   255   255   255   192
            192   192   192   192   192   192   192   192   192   128
            192   192   192   192   192   192   192   192   192   128
            0     0   192   192   192   192   192   192   192   128
            255   255     0     0   192   192   192   192   192   128
            255   255   255   255     0   192   192   192   192   128
            255   255   255   255   255     0   192   192   192   128
            255   255   255   255   255   255     0   192   192   128
            255     0     0   255   255   255     0   192   192   128
            255     0     0   255   255   255   255     0   192   128
            255   255   255   255   255   255   255     0   192   128
            255   255   255   255   255   255   255     0   192   128
            255   255   255   255   255   255   255     0   192   128
            255   255   255     0   255   255   255     0   192   128
            255   255     0   255   255   255     0   192   192   128
            0     0   255   255   255   255     0   192   192   128
            255   255   255   255   255     0   192   192   192   128
            255   255   255   255     0   192   192   192   192   128
            255   255     0     0   192   192   192   192   192   128
            0     0   192   192   192   192   192   192   192   128
            192   192   192   192   192   192   192   192   192   128
            128   128   128   128   128   128   128   128   128   128
        ]];
    
    Matrix(:,:,3) = [[
            255   255   255   255   255   255   255   255   255   255   255   255   255
            255   255   255   255   255   255   255   255   255   255   255   255   255
            255   255   192   192   192   192   192   192   192   192   192   192   192
            255   255   192   192   192   192   192   192   192   192   192   192   192
            255   255   192   192   192   192   192   192   192   192     0     0     0
            255   255   192   192   192   192   192   192     0     0     0     0     0
            255   255   192   192   192   192   192     0     0     0     0     0     0
            255   255   192   192   192   192     0     0     0     0     0     0     0
            255   255   192   192   192     0     0     0     0     0     0     0     0
            255   255   192   192   192     0     0     0     0     0     0     0     0
            255   255   192   192     0     0     0     0     0     0     0     0     0
            255   255   192   192     0     0     0     0     0     0     0     0     0
            255   255   192   192     0     0     0     0     0     0     0     0     0
            255   255   192   192     0     0     0     0     0     0     0     0     0
            255   255   192   192     0     0     0     0     0     0     0     0     0
            255   255   192   192   192     0     0     0     0     0     0     0     0
            255   255   192   192   192     0     0     0     0     0     0     0     0
            255   255   192   192   192   192     0     0     0     0     0     0     0
            255   255   192   192   192   192   192     0     0     0     0     0     0
            255   255   192   192   192   192   192   192     0     0     0     0     0
            255   255   192   192   192   192   192   192   192   192     0     0     0
            255   255   192   192   192   192   192   192   192   192   192   192   192
            255   192   128   128   128   128   128   128   128   128   128   128   128
        ],[
            255   255   255   255   255   255   255   255   255   255
            255   255   255   255   255   255   255   255   255   192
            192   192   192   192   192   192   192   192   192   128
            192   192   192   192   192   192   192   192   192   128
            0     0   192   192   192   192   192   192   192   128
            0     0     0     0   192   192   192   192   192   128
            0     0     0     0     0   192   192   192   192   128
            0     0     0     0     0     0   192   192   192   128
            0     0     0     0     0     0     0   192   192   128
            0     0     0     0     0     0     0   192   192   128
            0     0     0     0     0     0     0     0   192   128
            0     0     0     0     0     0     0     0   192   128
            0     0     0     0     0     0     0     0   192   128
            0     0     0     0     0     0     0     0   192   128
            0     0     0     0     0     0     0     0   192   128
            0     0     0     0     0     0     0   192   192   128
            0     0     0     0     0     0     0   192   192   128
            0     0     0     0     0     0   192   192   192   128
            0     0     0     0     0   192   192   192   192   128
            0     0     0     0   192   192   192   192   192   128
            0     0   192   192   192   192   192   192   192   128
            192   192   192   192   192   192   192   192   192   128
            128   128   128   128   128   128   128   128   128   128
        ]];
else % Cry
    Matrix(:,:,1) = [[
            128   128   128   128   128   128   128   128   128   128   128   128   128
            128   255   255   255   255   255   255   255   255   255   255   255   255
            128   255   255   255   255   255   255   255   255   255   255   255   255
            128   255   255   192   192   192   192   192   192   192   192   192   192
            128   255   255   192   192   192   192   192   192   192   192   192   192
            128   255   255   192   192   192   192   192   192   192   192     0     0
            128   255   255   192   192   192   192   192   192     0     0   255   255
            128   255   255   192   192   192   192   192     0   255   255   255   255
            128   255   255   192   192   192   192     0   255   255   255   255   255
            128   255   255   192   192   192     0   255   255     0   255     0   255
            128   255   255   192   192   192     0   255   255   255     0   255   255
            128   255   255   192   192     0   255   255   255     0   255     0   255
            128   255   255   192   192     0   255   255   255   255   255   255   255
            128   255   255   192   192     0   255   255   255   255   255   255   255
            128   255   255   192   192     0   255   255   255   255   255   255   255
            128   255   255   192   192     0   255   255   255   255   255     0     0
            128   255   255   192   192   192     0   255   255   255     0   255   255
            128   255   255   192   192   192     0   255   255     0   255   255   255
            128   255   255   192   192   192   192     0   255   255   255   255   255
            128   255   255   192   192   192   192   192     0   255   255   255   255
            128   255   255   192   192   192   192   192   192     0     0   255   255
            128   255   255   192   192   192   192   192   192   192   192     0     0
            128   255   255   192   192   192   192   192   192   192   192   192   192
        ],[
            128   128   128   128   128   128   128   128   128   128   128   128
            255   255   255   255   255   255   255   255   255   255   255   192
            255   255   255   255   255   255   255   255   255   255   192   128
            192   192   192   192   192   192   192   192   192   192   128   128
            192   192   192   192   192   192   192   192   192   192   128   128
            0     0     0   192   192   192   192   192   192   192   128   128
            255   255   255     0     0   192   192   192   192   192   128   128
            255   255   255   255   255     0   192   192   192   192   128   128
            255   255   255   255   255   255     0   192   192   192   128   128
            255   255     0   255     0   255   255     0   192   192   128   128
            255   255   255     0   255   255   255     0   192   192   128   128
            255   255     0   255     0   255   255   255     0   192   128   128
            255   255   255   255   255   255   255   255     0   192   128   128
            255   255   255   255   255   255   255   255     0   192   128   128
            255   255   255   255   255   255   255   255     0   192   128   128
            0     0     0   255   255   255   255   255     0   192   128   128
            255   255   255     0   255   255   255     0   192   192   128   128
            255   255   255   255     0   255   255     0   192   192   128   128
            255   255   255   255   255   255     0   192   192   192   128   128
            255   255   255   255   255     0   192   192   192   192   128   128
            255   255   255     0     0   192   192   192   192   192   128   128
            0     0     0   192   192   192   192   192   192   192   128   128
            192   192   192   192   192   192   192   192   192   192   128   128
        ]] ;
    Matrix(:,:,2) = [[
            128   128   128   128   128   128   128   128   128   128   128   128   128
            128   255   255   255   255   255   255   255   255   255   255   255   255
            128   255   255   255   255   255   255   255   255   255   255   255   255
            128   255   255   192   192   192   192   192   192   192   192   192   192
            128   255   255   192   192   192   192   192   192   192   192   192   192
            128   255   255   192   192   192   192   192   192   192   192     0     0
            128   255   255   192   192   192   192   192   192     0     0   255   255
            128   255   255   192   192   192   192   192     0   255   255   255   255
            128   255   255   192   192   192   192     0   255   255   255   255   255
            128   255   255   192   192   192     0   255   255     0   255     0   255
            128   255   255   192   192   192     0   255   255   255     0   255   255
            128   255   255   192   192     0   255   255   255     0   255     0   255
            128   255   255   192   192     0   255   255   255   255   255   255   255
            128   255   255   192   192     0   255   255   255   255   255   255   255
            128   255   255   192   192     0   255   255   255   255   255   255   255
            128   255   255   192   192     0   255   255   255   255   255     0     0
            128   255   255   192   192   192     0   255   255   255     0   255   255
            128   255   255   192   192   192     0   255   255     0   255   255   255
            128   255   255   192   192   192   192     0   255   255   255   255   255
            128   255   255   192   192   192   192   192     0   255   255   255   255
            128   255   255   192   192   192   192   192   192     0     0   255   255
            128   255   255   192   192   192   192   192   192   192   192     0     0
            128   255   255   192   192   192   192   192   192   192   192   192   192
        ],[
            128   128   128   128   128   128   128   128   128   128   128   128
            255   255   255   255   255   255   255   255   255   255   255   192
            255   255   255   255   255   255   255   255   255   255   192   128
            192   192   192   192   192   192   192   192   192   192   128   128
            192   192   192   192   192   192   192   192   192   192   128   128
            0     0     0   192   192   192   192   192   192   192   128   128
            255   255   255     0     0   192   192   192   192   192   128   128
            255   255   255   255   255     0   192   192   192   192   128   128
            255   255   255   255   255   255     0   192   192   192   128   128
            255   255     0   255     0   255   255     0   192   192   128   128
            255   255   255     0   255   255   255     0   192   192   128   128
            255   255     0   255     0   255   255   255     0   192   128   128
            255   255   255   255   255   255   255   255     0   192   128   128
            255   255   255   255   255   255   255   255     0   192   128   128
            255   255   255   255   255   255   255   255     0   192   128   128
            0     0     0   255   255   255   255   255     0   192   128   128
            255   255   255     0   255   255   255     0   192   192   128   128
            255   255   255   255     0   255   255     0   192   192   128   128
            255   255   255   255   255   255     0   192   192   192   128   128
            255   255   255   255   255     0   192   192   192   192   128   128
            255   255   255     0     0   192   192   192   192   192   128   128
            0     0     0   192   192   192   192   192   192   192   128   128
            192   192   192   192   192   192   192   192   192   192   128   128
        ]] ;
    Matrix(:,:,3) = [[
            128   128   128   128   128   128   128   128   128   128   128   128   128
            128   255   255   255   255   255   255   255   255   255   255   255   255
            128   255   255   255   255   255   255   255   255   255   255   255   255
            128   255   255   192   192   192   192   192   192   192   192   192   192
            128   255   255   192   192   192   192   192   192   192   192   192   192
            128   255   255   192   192   192   192   192   192   192   192     0     0
            128   255   255   192   192   192   192   192   192     0     0     0     0
            128   255   255   192   192   192   192   192     0     0     0     0     0
            128   255   255   192   192   192   192     0     0     0     0     0     0
            128   255   255   192   192   192     0     0     0     0     0     0     0
            128   255   255   192   192   192     0     0     0     0     0     0     0
            128   255   255   192   192     0     0     0     0     0     0     0     0
            128   255   255   192   192     0     0     0     0     0     0     0     0
            128   255   255   192   192     0     0     0     0     0     0     0     0
            128   255   255   192   192     0     0     0     0     0     0     0     0
            128   255   255   192   192     0     0     0     0     0     0     0     0
            128   255   255   192   192   192     0     0     0     0     0     0     0
            128   255   255   192   192   192     0     0     0     0     0     0     0
            128   255   255   192   192   192   192     0     0     0     0     0     0
            128   255   255   192   192   192   192   192     0     0     0     0     0
            128   255   255   192   192   192   192   192   192     0     0     0     0
            128   255   255   192   192   192   192   192   192   192   192     0     0
            128   255   255   192   192   192   192   192   192   192   192   192   192
        ],[
            128   128   128   128   128   128   128   128   128   128   128   128
            255   255   255   255   255   255   255   255   255   255   255   192
            255   255   255   255   255   255   255   255   255   255   192   128
            192   192   192   192   192   192   192   192   192   192   128   128
            192   192   192   192   192   192   192   192   192   192   128   128
            0     0     0   192   192   192   192   192   192   192   128   128
            0     0     0     0     0   192   192   192   192   192   128   128
            0     0     0     0     0     0   192   192   192   192   128   128
            0     0     0     0     0     0     0   192   192   192   128   128
            0     0     0     0     0     0     0     0   192   192   128   128
            0     0     0     0     0     0     0     0   192   192   128   128
            0     0     0     0     0     0     0     0     0   192   128   128
            0     0     0     0     0     0     0     0     0   192   128   128
            0     0     0     0     0     0     0     0     0   192   128   128
            0     0     0     0     0     0     0     0     0   192   128   128
            0     0     0     0     0     0     0     0     0   192   128   128
            0     0     0     0     0     0     0     0   192   192   128   128
            0     0     0     0     0     0     0     0   192   192   128   128
            0     0     0     0     0     0     0   192   192   192   128   128
            0     0     0     0     0     0   192   192   192   192   128   128
            0     0     0     0     0   192   192   192   192   192   128   128
            0     0     0   192   192   192   192   192   192   192   128   128
            192   192   192   192   192   192   192   192   192   192   128   128
        ]] ;
end

% -------------------------------------------------------------------------
function Keypress_fcn( h )

handles = guidata( h ) ;

CurrentKey = get( handles.NewClearMine, 'CurrentKey' ) ;
CurrentCharacter = get( handles.NewClearMine, 'CurrentCharacter' ) ;

if strcmp(CurrentKey, 'f2')
    BeginMenu_Callback( handles.NewClearMine ) ;
elseif  strcmp(CurrentKey, 'return')
    if strcmp( CurrentCharacter, char(10))
        GameIsBegin = getappdata( handles.NewClearMine, 'GameIsBegin' ) ;        
        if isempty( GameIsBegin )
            return ;    
        end        
        MineNumberArray = getappdata( handles.NewClearMine, 'MineNumberArray' ) ;
        if isempty(MineNumberArray)
            return ;
        end
        
        setappdata( handles.NewClearMine, 'GameOver', 1 ) ;
        
        CData = get( handles.MainPatch, 'FaceVertexCData' ) ;       
        
        ZeroIndex = find( MineNumberArray == 0 ) ;
        
        cla( [handles.MainFrame,handles.MainPatch] ) ;
        
        GameInfo = getappdata( handles.NewClearMine, 'GameInfo' ) ;
        RowNumber = GameInfo.RowNumber ;
        ColNumber = GameInfo.ColNumber ;
        TotalMineNumber = GameInfo.MineNumber ;
        
        ButtonPosition = getappdata( handles.NewClearMine, 'ButtonPosition' ) ;
        ButtonWidth = getappdata( handles.NewClearMine, 'ButtonWidth' ) ;
        
        XPos = ButtonPosition(1) ;
        YPos = ButtonPosition(2) ;

        ColorArray = [0 0 1;0 1 0;1 0 0;0 1 1;1 0 1;1 1 0;0 0 0;0 0 1;1 1 0] ;
        for num = 1: numel(MineNumberArray)
            TempMineNumber = MineNumberArray(num) ;        
            if TempMineNumber~=0
                XIndex = ceil(num/RowNumber)-1 ;
                YIndex = mod((num-1), RowNumber)+1 ;
                TextXPos = (XIndex + 0.5) * ButtonWidth + XPos ;
                TextYPos = YPos - (YIndex + 0.5) * ButtonWidth + ButtonWidth ;
                if isnan(TempMineNumber)
                    text( TextXPos, TextYPos, '●', 'Color', 'k',...
                        'Parent', handles.MainAxes, 'HorizontalAlignment', 'center', 'FontSize',13 ) ;
                else
                    text( TextXPos, TextYPos, num2str(TempMineNumber), 'Color', ColorArray(TempMineNumber,:),...
                        'Parent', handles.MainAxes, 'HorizontalAlignment', 'center', 'FontSize',13 ) ;
                end
            end
        end
        CData(:,:) = 0.85 ;
        set( handles.MainPatch, 'FaceVertexCData', CData ) ;
    end
else 
    return 
end