
# The following lines were added by compinstall

WALLPATH="/home/quentin/walls/dracula/arch.png"
PATH=~/.local/bin:$PATH

export VISUAL="code"
export EDITOR="nano"
export PAGER="less"
export TERMCMD="st"

autoload -U colors && colors
PS1="%{$fg[magenta]%}[%@] %B%{$fg[blue]%}%n%{$fg[magenta]%} %~%{$reset_color%} $%b "

zstyle ':completion:*' completer _complete _ignored _approximate
zstyle ':completion:*' expand prefix suffix
zstyle ':completion:*' ignore-parents parent pwd
zstyle ':completion:*' insert-unambiguous true
zstyle ':completion:*' list-colors ''
zstyle ':completion:*' list-prompt %SAt %p: Hit TAB for more, or the character to insert%
zstyle ':completion:*' list-suffixes true
zstyle ':completion:*' matcher-list '' 'm:{[:lower:]}={[:upper:]}' 'r:|[._-]=* r:|=*'
zstyle ':completion:*' menu select=1
zstyle ':completion:*' original false
zstyle ':completion:*' select-prompt %SScrolling active: current selection at %p%s
zstyle ':completion:*' squeeze-slashes true
zstyle :compinstall filename '/home/quentin/.zshrc'

autoload -U compinit
compinit

# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=100000
SAVEHIST=100000
unsetopt beep
bindkey -e
# End of lines configured by zsh-newuser-install

# aliases
alias \
	cp="cp -iv" \
	mv="mv -iv" \
	rm="rm -vI" \
	bc="bc -ql" \
	rsync="rsync -vrPlu" \
	mkd="mkdir -pv" \
	yt="yt-dlp --embed-metadata -i" \
	yta="yt -x -f bestaudio/best" \
	ytt="yt --skip-download --write-thumbnail" \
	ffmpeg="ffmpeg -hide_banner"

alias \
	ls="ls -hN --color=auto --group-directories-first" \
	grep="grep --color=auto" \
	diff="diff --color=auto" \
	ccat="highlight --out-format=ansi" \
	ip="ip -color=auto"

alias \
	cat="bat --color=auto" \
	ls="exa --color=auto" \
	ll="exa -l --header --git --icons --color=auto" \
	lt="exa -l --header --git --icons --tree --color=auto" \
	la="ll -a" \
	find="fd" \
	du="dust"

# auto cd
setopt autocd

source /usr/share/zsh/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh

ZSH_AUTOSUGGEST_STRATEGY=(history completion)
bindkey '^ ' autosuggest-accept

# wal -i $WALLPATH --backend colorz &> /dev/null
# echo "\n"
# neofetch --ascii_colors 4 4 --ascii_distro arch --colors 4 7 7 4 4 7
source /usr/share/zsh/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.plugin.zsh 2>/dev/null

eval "$(starship init zsh)"
eval "$(zoxide init --cmd cd zsh)"
