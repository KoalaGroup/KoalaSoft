MQ Implementation in KoalaSoft
==============================

# Device List #

## Samplers ##

### KoaMQEmsSampler ###

### KoaMQSampler ###
**Function:**
Read ROOT with standard structure or ems raw binary file as input. Send out the branches to output.
Receive the ack message from the last device to signal the end of reading task.

**Usage:**
Binary: koala-sampler
Parameters:
- file-name (comma separated input file pathes)
- branch-name (comma separated branches to be read from input file and send out)
- max-index (number of events to be read out)
- out-channel (output channel name)
- ack-channel (acknowledga channel to receive ack message from last device, normally Sink-type, in the pipeline)
- sampler-type (the default is FairFileSource, the other option is KoaDigiSource**

**Channels:**
Input: NONE
Output: 1 CH with 1 sub-CH
Ack: 1 CH with 1 sub-CH

**Messages:**
FairMQParts

**Notes:**
- Ack channel should be PULL type.
- Any branch with class inherited from TObject could be readout and sendout to next device
- The branch objects are bundled as FairMQParts and send out to the output

### KoaMQSimDevice ###

## Task Processor ##

## Sinks ##

### KoaMQSink ###
**Functions:**
Receive branches from upstream devices and store these objects in ROOT file.
Send the ack message each time a new message is received.

**Usage:**
Binary: koala_sink
Parameters:
- file-name (name of the output file, a suffix may be added in the filename) 
- class-name (comma separated class name of a branch, it can only be FairEventHeader, FairMCEventHeader or TClonesArray(SpecifiClassName))
- branch-name (comma separated branch name of a branch, corresponding to class-name)
- in-channel (input channel name)
- ack-channel (acknowledge channel to send ack message to the first device in the pipeline, normally it's Sampler**

**Channels**
Input: 1 CH with 1 sub-CH
Output: NONE
Ack: 1 CH with 1 sub-CH

**Messages:**
FairMQParts

**Notes:**
- Ack channel should be PUSH type
- Only branches with following class name are allowed:
  - FairEventHeader
  - FairMCEventHeader
  - TClonesArray(SpecifiClassName)
- Output file structure:
  - cbmout (TTree): containing all the event-based data
  - BranchList (TList): name of all the branches in the cbmout tree
  - cbmroot (TFolder):
    - EvtHeader (TFolder): objects of FairEventHeader and FairMCEventHeader
    - Koala (TFolder**: objects of TClonesArray

## Histogram Server ##

### KoaMQHistServer ###
**Functions:**

**Usage:**

**Channels:**

**Messages**

**Notes:**
- Work in SUBSCRIBE-type bind-method, tasks which generates histograms in PUBLISH-type connect-method
## Auxiliary Devices ##
Some of the auxiliary devices are common devices from FairMQ or FairRoot codebase.

### FairMQMerger ###
**Function:** 
Relaying messages from multiple inputs to one output channel.

**Usage:**
Provided by FairMQ.
Binary: fairmq-merger
Parameters: in-channel (input channel name), out-channel(output channel name), multipart(FairMQParts or FairMQMessage)

**Channels:** 
Input: 1 CH with N sub-CH
Output: 1 CH with 1 sub-CH

**Messages:** 
The message could be FairMQMessage or FairMQParts.

**Note:** 
It does not further process the input messages, just relay them to the output channel.

### FairMQSink ###
**Function:**
Acting as a trash sink, i.e. it receives any message from the input channel and then simply discards them.

**Usage:**
Provided by FairMQ.
Binary: fairmq-sink
Parameters: in-channel (input channel name), multipart(FairMQParts or FairMQMessage)

**Channels:**
Input: 1 CH with 1 sub-CH
Output: NONE

**Messages:**
The message could be FairMQMessage or FairMQParts.

**Notes:**
Using FairMQMerger and FairMQSink together, message from multiple devices can be trashed.

### FairMQSplitter ###
**Function:**
Split the input messages to multiple outputs using round-robin strategy.

**Usage:**
Provided by FairMQ.
Binary: fairmq-splitter
Parameters: in-channel (input channel name), out-channel(output channel name), multipart(FairMQParts or FairMQMessage)

**Channels:**
Input: 1 CH with 1 sub-CH
Output: 1 CH with N sub-CH

**Messages:**
The message could be FairMQMessage or FairMQParts.

**Notes:**

### FairMQMultiplier ###
**Function:**
Copy the input message to multiple outputs

**Usage:**
Provided by FairMQ.
Binary: fairmq-multiplier
Parameters: in-channel (input channel name), out-channel(comma separated output channel names), multipart(FairMQParts or FairMQMessage)

**Channels:**
Input: 1 CH with 1 sub-CH
Output: N CH with N sub-CH

**Messages:**
The message could be FairMQMessage or FairMQParts.

**Notes:**

